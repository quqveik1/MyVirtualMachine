
#pragma once

#include <iostream>
#include <string>

#include "..\StringSort\WStringFnc.cpp"

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.h"
#include "Commands.cpp"
#include <charconv>

COMMANDTYPE commandsArr[cCommands + 1]{};

void readByteCode(std::wstring path)
{
    initCommandsArr();

    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::wstring_view fullText;
    readText(path, &fullText);

    readAndExecuteCommands(fullText);

    delete fullText.data();
}

void initCommandsArr()
{
    commandsArr[in_num] = in_command;
    commandsArr[out_num] = out_command;
    commandsArr[push_num] = push_command;
    commandsArr[hlt_num] = hlt_command;
    commandsArr[add_num] = add_command;
    commandsArr[sub_num] = sub_command;
    commandsArr[mul_num] = mul_command;
    commandsArr[div_num] = div_command;
}

void readAndExecuteCommands(std::wstring_view& text)
{
    int callCode = CommandReadErrorCode;
    int lastLine = 0;

    std::wstring_view* textLines = NULL;
    int stramount = separateTextByLinesToArr(text, &textLines);

    for(int i = 0; i < stramount; i++)
    {
        lastLine++;

        callCode = executeCommand(textLines[i]);
        if(callCode != WellCode)
        {
            break;
        }
    }

    endProgramWithCode(callCode, lastLine - 1, textLines[lastLine - 1]);
}

int readIntCommands(int* commandsArr, std::wstring path)
{
    return 0;
}

void endProgramWithCode(int code, int lastLine, std::wstring_view& lastStr)
{
    if(code == CommandBreakCode)
    {
        std::cout << "Программа завершилась удачно\n";
    }
    else
    {
        std::cout << "Программа неудачно завершилась с кодом: " << code << std::endl;
        std::cout << "Программа возникла в строке [" << lastLine << "]: " << std::endl;
        std::wcout << L"\"" << lastStr << L"\"" << std::endl;
    }
}

int executeCommand(std::wstring_view& command)
{
    std::wstring_view commandName{};
    std::wstring_view commandData{};

    splitCommand(command, commandName, commandData);

    int callRes = callCommandByName(commandName, commandData);

    return callRes;
}

int callCommandByName(std::wstring_view& commandName, std::wstring_view& commandData)
{
    int res = CommandReadErrorCode;
    int commandNum = std::stoi(std::wstring(commandName));

    if (commandNum >= 0)
    {
        res = commandsArr[commandNum](AppRuntimeData, commandData);
    }

    //длина команды * количество команд * количество команд в файле * позиция команды в списке из которого мы выбираем
    return res;
}

void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData)
{
    int spacePos = findFirstSpacePos(fullCommand);
    commandName = fullCommand.substr(0, spacePos);
    if(spacePos >= 0)
    {
        commandData = fullCommand.substr(spacePos + 1);
    }
}

int findFirstSpacePos(std::wstring_view& fullCommand)
{
    for(int i = 0; i < (int)fullCommand.size(); i++)
    {
        if (fullCommand[i] == ' ')
        {
            return i;
        }
    }
    return -1;
}