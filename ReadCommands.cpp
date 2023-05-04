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
    std::ifstream file("..\\kvm.bc");

    std::string_view fullText;

    std::stringstream stringstream;

    stringstream << file.rdbuf();

    fullText = stringstream.str();

    readAndExecuteCommands(fullText);

    file.close();
}

void readAndExecuteCommands(std::string_view& text)
{
    int start = 0;
    std::string_view textCommand;

    for (int i = 0; ; i++)
    {
        if (start <= i)
        {
            if (i == text.size())
            {
                textCommand = text.substr(start, i - start);
                executeCommand(textCommand);
                return;
            }
            else if (text[i] == '\n')
            {
                textCommand = text.substr(start, i - start);
                start = i + 1;

                int callRes = executeCommand(textCommand);
                if(callRes == CommandBreakCode)
                {
                    return;
                }
            }
        }
    }
}

int executeCommand(std::string_view& command)
{
    std::string_view commandName;
    std::string_view commandData;

    splitCommand(command, commandName, commandData);

    int callRes = callCommandByName(commandName, commandData);

    return callRes;
}

int callCommandByName(std::string_view& commandName, std::string_view& commandData)
{
    int res = CommandBreakCode;
    if(commandName == in_str)
    {
        res = in_command(AppRuntimeData, commandData);
    }
    else if(commandName == out_str)
    {
        res = out_command(AppRuntimeData, commandData);
    }
    else if(commandName == hlt_str)
    {
        res = hlt_command(AppRuntimeData, commandData);
    }

    return res;
}

void splitCommand(std::string_view& fullCommand, std::string_view& commandName, std::string_view& commandData)
{
    int spacePos = findFirstSpacePos(fullCommand);
    commandName = fullCommand.substr(0, spacePos);
    commandData = fullCommand.substr(spacePos + 1);
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

