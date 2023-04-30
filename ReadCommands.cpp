//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.h"

void readByteCode()
{
    std::ifstream file("..\\kvm.bc");

    bool isFileOpen = file.is_open();

    char buffer[OneLineSize]{};
    char commandName[OneLineSize]{};
    char commandData[OneLineSize]{};

    for (;;)
    {
        if (file.getline(buffer, OneLineSize))
        {
            sscanf(buffer, "%s %[...]", commandName, commandData);
            std::cout << buffer << std::endl;
        }
        else
        {
            break;
        }

    }

    file.close();
}

int addCommandToStack(char* command, char* data)
{
    if(!strcmp(command, in_str))
    {

    }
    return 0;
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

