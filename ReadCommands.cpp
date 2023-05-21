
#pragma once

#include <iostream>
#include <string>

#include "..\StringSort\WStringFnc.cpp"

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.h"
#include "Commands.cpp"

void readByteCode(std::wstring path)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::wstring_view fullText;
    readText(path, &fullText);

    readAndExecuteCommands(fullText);

    delete fullText.data();
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

    if(_wcsnicmp(commandName.data(), in_strnum, commandName.size()) == 0)
    {
        res = in_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), out_strnum, commandName.size()) == 0)
    {
        res = out_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), push_strnum, commandName.size()) == 0)
    {
        res = push_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), hlt_strnum, commandName.size()) == 0)
    {
        res = hlt_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), add_strnum, commandName.size()) == 0)
    {
        res = add_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), sub_strnum, commandName.size()) == 0)
    {
        res = sub_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), mul_strnum, commandName.size()) == 0)
    {
        res = mul_command(AppRuntimeData, commandData);
    }

    else if(_wcsnicmp(commandName.data(), div_strnum, commandName.size()) == 0)
    {
        res = div_command(AppRuntimeData, commandData);
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