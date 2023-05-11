//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.h"
#include "Commands.cpp"

void readByteCode()
{
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());
    std::ifstream file("..\\kvm.bc");

    std::string_view fullText;

    std::stringstream stringstream;

    stringstream << file.rdbuf();

    std::string fullTextString = stringstream.str();
    fullText = fullTextString;

    readAndExecuteCommands(fullText);

    file.close();
}

void readAndExecuteCommands(std::string_view& text)
{
    int start = 0;
    std::string_view textCommand;

    int callCode = CommandReadErrorCode;
    int lastLine = 0;

    for (int i = 0; ; i++)
    {
        if (start <= i)
        {
            if (i > text.size())
            {
                lastLine++;
                textCommand = {};
                callCode = CommandEndFileErrorCode;
                break;
            }
            if (i == text.size() || text[i] == '\n')
            {
                lastLine++;
                textCommand = text.substr(start, i - start);
                start = i + 1;

                callCode = executeCommand(textCommand);
                if(callCode != WellCode)
                {
                    break;
                }
            }
        }
    }

    endProgramWithCode(callCode, lastLine - 1, textCommand);
}

void endProgramWithCode(int code, int lastLine, std::string_view& lastStr)
{
    if(code == CommandBreakCode)
    {
        std::cout << "Программа завершилась удачно\n";
    }
    else
    {
        std::cerr << "Программа неудачно завершилась с кодом: " << code << std::endl;
        std::cerr << "Программа возникла в строке [" << lastLine << "]: " << std::endl;
        std::cerr << "\"" << lastStr << "\"" << std::endl;
    }
}

int executeCommand(std::string_view& command)
{
    std::string_view commandName{};
    std::string_view commandData{};

    splitCommand(command, commandName, commandData);

    int callRes = callCommandByName(commandName, commandData);

    return callRes;
}

int callCommandByName(std::string_view& commandName, std::string_view& commandData)
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

void splitCommand(std::string_view& fullCommand, std::string_view& commandName, std::string_view& commandData)
{
    int spacePos = findFirstSpacePos(fullCommand);
    commandName = fullCommand.substr(0, spacePos);
    if(spacePos >= 0)
    {
        commandData = fullCommand.substr(spacePos + 1);
    }
}

int findFirstSpacePos(std::string_view& fullCommand)
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

