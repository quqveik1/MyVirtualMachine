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

    if (readRes == WellCode)
    {
        std::thread t(&Processor::startUiThread, this);
        readAndExecuteCommands();
        t.join();
    }
    else
    {
        std::cout << "Проблема запуска скомпилированного байткода: " << readRes << std::endl;
    }

    return WellCode;
}

void Processor::startUiThread()
{
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), "My Window");
    //window.setFramerateLimit(60);

    while (window.isOpen())
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
        window.display();
    }
}

ErrorCode Processor::readFile(std::string& path)
{
    FILE* file = fopen(path.c_str(), "r");

    FileHeader fileHeader{};

    fread(&fileHeader, sizeof(FileHeader), 1, file);

    bool valRes = fileHeader.validate();

    if (!valRes)
    {
        std::cout << "Ошибка чтения заголовка файла\n";
        return FileHeaderReadErrorCode;
    }

    long size = fileSize(file);

    DataStack& dataStack = getCommandData();

    dataStack.setSize(size);
    dataStack.setArr(new char[size]);

    fread(dataStack.getArr(), sizeof(char), size, file);

    fclose(file);
    return WellCode;
}

void Processor::readAndExecuteCommands()
{
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), "My Window");

    int callCode = CommandReadErrorCode;

    for (int i = 0; ; i++)
    {
        callCode = executeCommand();
        if (callCode != WellCode)
        {
            break;
        }

        
    }

    endProgramWithCode(callCode);
}

void Processor::endProgramWithCode(int code)
{

    if (code == CommandBreakCode)
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

int Processor::executeCommand()
{
    int filePos = getCommandData().getCurrPos();

    int codedCommandNum = *getCommandData().peek<int>();
    getBreakpoints().observeBreakpoints();


    int commandNum = decodeNumberRepresentation(codedCommandNum, NULL, NULL);

    if (isCommandNumValid(commandNum))
    {
        COMMANDTYPE fnc = commandsArr[commandNum];
        if (fnc)
        {
            int callRes = fnc(*this, codedCommandNum);

            getRuntimeInfoCollector().addLastCommand(filePos, commandNum);

            return callRes;
        }
    }

    return CommandReadErrorCode;
}