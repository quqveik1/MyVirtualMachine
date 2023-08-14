#pragma once

#include "Processor.h"

#include <thread>
#include <SFML/Graphics.hpp>

#include "CallStack.cpp"
#include "ProcessorDebug/RuntimeInfoCollector.cpp"
#include "BreakPoint/Breakpoints.cpp"
#include "FileHeader.cpp"
#include "../InteractiveMode/InteractiveCode.h"
#include "../InteractiveMode/InteractiveMode.h"

Processor::Processor() :
    callStack(this),
    runtimeInfoCollector(*this),
    breakpoints(this)
{
};

ErrorCode Processor::startExecutingProgramm(std::string& path)
{
    ErrorCode readRes = readFile(path);

    if (readRes == ErrorCode::WellCode)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::thread t(&Processor::startUiThread, this);
        t.detach();
        //sf::RenderWindow window(sf::VideoMode(xSize, ySize), "My Window", sf::Style::Titlebar);
        //window.setFramerateLimit(60);
        //program_window = &window;
        
        readAndExecuteCommands();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << "Time elapsed: " << elapsed.count() << " ms" << std::endl;
        isProgrammActive = false;
    }
    else
    {
        std::cout << "Проблема запуска скомпилированного байткода: " << (int)readRes << std::endl;
    }

    return ErrorCode::WellCode;
}

void Processor::startUiThread()
{
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), "My Window", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    while(isProgrammActive)
    {
        //auto start = std::chrono::high_resolution_clock::now();
        observeFrame(window);
        //auto end = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<double, std::milli> elapsed = end - start;

        //std::cout << "Time frame: " << elapsed.count() << " ms" << std::endl;
    }
}

void Processor::observeFrame(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            break;
        }

    }

    window.clear();

    drawFrame(window);

    window.display();
}

void Processor::drawFrame(sf::RenderWindow& window)
{
    drawLines(window);
    drawVram(window);
}

void Processor::drawLines(sf::RenderWindow& window)
{
    const int colorLine = 0x808080;
    const int lineDeltaX = window.getSize().x / appRAM.xSize;
    const int lineDeltaY = window.getSize().y / appRAM.ySize;

    const sf::Color lineColor(80, 80, 80);

    for (unsigned int x = lineDeltaX; x < window.getSize().x; x += lineDeltaX)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f((float)x, 0);
        line[1].position = sf::Vector2f((float)x, (float)window.getSize().y);
        line[0].color = lineColor;
        line[1].color = lineColor;

        window.draw(line);
    }

    for (unsigned int y = lineDeltaY; y < window.getSize().y; y += lineDeltaY)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(0, (float)y);
        line[1].position = sf::Vector2f((float)window.getSize().x, (float)y);
        line[0].color = lineColor;
        line[1].color = lineColor;

        window.draw(line);
    }
}

void Processor::drawVram(sf::RenderWindow& window)
{
    const int pixelSizeX = window.getSize().x / appRAM.xSize;
    const int pixelSizeY = window.getSize().y / appRAM.ySize;

    for (int x = 0; x < getAppRAM().xSize; x ++)
    {
        for (int y = 0; y < getAppRAM().ySize; y ++)
        {
            int colorCode = getAppRAM().getPixel(x, y);

            sf::RectangleShape pixel(sf::Vector2f((float)pixelSizeX - 1, (float)pixelSizeY - 1));
            pixel.setPosition((float)x * pixelSizeX, (float)y * pixelSizeY);

            sf::Color color(colorCode);

            pixel.setFillColor(color);

            window.draw(pixel);
        }
    }
}

ErrorCode Processor::readFile(std::string& path)
{
    FILE* file = fopen(path.c_str(), "rb");

    FileHeader fileHeader{};

    fread(&fileHeader, sizeof(FileHeader), 1, file);

    bool valRes = fileHeader.validate();

    if (!valRes)
    {
        std::cout << "Ошибка чтения заголовка файла\n";
        return ErrorCode::FileHeaderReadErrorCode;
    }

    long size = fileSize(file);

    DataStack& dataStack = getCommandData();

    dataStack.setSize(size);
    dataStack.setArr(new char[size]);

    fread(dataStack.getArr(), sizeof(char), size, file);

    fclose(file);
    return ErrorCode::WellCode;
}

void Processor::readAndExecuteCommands()
{
    ErrorCode callCode = ErrorCode::CommandReadErrorCode;

    for (;;)
    {
        callCode = executeCommand();
        if (callCode != ErrorCode::WellCode)
        {
            break;
        }

        //observeFrame(*program_window);
    }

    endProgramWithCode(callCode);
}

void Processor::endProgramWithCode(ErrorCode code)
{

    if (code == ErrorCode::CommandBreakCode)
    {
        std::cout << "\nПрограмма завершилась удачно\n";
    }
    else
    {
        InteractiveCode interCode = ContinueInteractiveMode;
        startInteractiveMode(*this, (ErrorCode)code, interCode);
        if (interCode == ContinueAppExecuting)
        {
            readAndExecuteCommands();
        }
    }
}

ErrorCode Processor::executeCommand()
{
    int filePos = getCommandData().getCurrPos();

    int codedCommandNum = *getCommandData().peek<int>();
    getBreakpoints().observeBreakpoints();

    int commandNum = decodeNumberRepresentation(codedCommandNum, NULL, NULL);

    COMMANDTYPE fnc = getCommand(commandNum);
    if (fnc)
    {
        ErrorCode callRes = fnc(*this, codedCommandNum);

        getRuntimeInfoCollector().addLastCommand(filePos, codedCommandNum);

        return callRes;
    }

    return ErrorCode::CommandReadErrorCode;
}