//
// Created by Kurlic on 04.05.2023.
//
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
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    std::wstring_view fullText;
    readText(L"..\\kvm.bc", &fullText);

    readAndExecuteCommands(fullText);
}

void readAndExecuteCommands(std::wstring_view& text)
{
    int callCode = CommandReadErrorCode;
    int lastLine = 0;

    int stramount = findEOLsN_(text) + 1;
    std::wstring_view* textLines = new std::wstring_view[stramount]{};
    fromOneCharToStrings(text, textLines);

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
        std::cerr << "Программа неудачно завершилась с кодом: " << code << std::endl;
        std::cerr << "Программа возникла в строке [" << lastLine << "]: " << std::endl;
        std::wcerr << L"\"" << lastStr << L"\"" << std::endl;
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
    if(commandName == in_str)
    {
        res = in_command(AppRuntimeData, commandData);
    }

    else if(commandName == out_str)
    {
        res = out_command(AppRuntimeData, commandData);
    }

    else if(commandName == push_str)
    {
        res = push_command(AppRuntimeData, commandData);
    }

    else if(commandName == hlt_str)
    {
        res = hlt_command(AppRuntimeData, commandData);
    }

    else if(commandName == add_str)
    {
        res = add_command(AppRuntimeData, commandData);
    }

    else if(commandName == sub_str)
    {
        res = sub_command(AppRuntimeData, commandData);
    }

    else if(commandName == mul_str)
    {
        res = mul_command(AppRuntimeData, commandData);
    }

    else if(commandName == div_str)
    {
        res = div_command(AppRuntimeData, commandData);
    }

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
    for(int i = 0; i < fullCommand.size(); i++)
    {
        if (fullCommand[i] == ' ')
        {
            return i;
        }
    }
    return -1;
}

void readInput()
{
    std::ifstream file("..\\runtimeData.txt");

    bool isFileOpen = file.is_open();

    std::string line;
    for(;;)
    {
        if(std::getline(file, line))
        {
            AppRuntimeData.getInput().push(line);
            std::cout << line << std::endl;
        }
        else
        {
            break;
        }
    }

    file.close();
}

