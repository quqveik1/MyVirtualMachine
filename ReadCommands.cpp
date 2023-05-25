
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "..\StringSort\WStringFnc.cpp"

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.h"
#include "Commands.cpp"
#include <charconv>
#include "FncArrs.cpp"


void readByteCode(std::string path)
{
    initCommandsArr();
    initSizeArr();

    setlocale(LC_ALL, "ru_RU.UTF-8");

    //std::wstring_view fullText;
    //readText(path, &fullText);
    
    FILE* file = fopen(path.c_str(), "r");

    long size = fileSize(file);

    DataStack dataStack;
    dataStack.setSize(size);
    dataStack.setArr(new char[size]);

    fread(dataStack.get(0), sizeof(char), size, file);

    fclose(file);
    


    readAndExecuteCommands(dataStack);
}

long fileSize(FILE* File)
{
    struct stat buff = {};
    buff.st_size = -1;

    fstat(_fileno(File), &buff);

    return buff.st_size;

}

void readAndExecuteCommands(DataStack& data)
{
    int callCode = CommandReadErrorCode;
    int lastLine = 0;

    for(int i = 0; ; i++)
    {
        lastLine++;

        callCode = executeCommand(data);
        if(callCode != WellCode)
        {
            break;
        }
    }

    endProgramWithCode(callCode, lastLine - 1);
}

int readIntCommands(int* commandsArr, std::wstring path)
{
    return 0;
}

void endProgramWithCode(int code, int lastLine)
{
    if(code == CommandBreakCode)
    {
        std::cout << "Программа завершилась удачно\n";
    }
    else
    {
        std::cout << "Программа неудачно завершилась с кодом: " << code << std::endl;
        //std::cout << "Программа возникла в строке [" << lastLine << "]: " << std::endl;
        //std::wcout << L"\"" << lastStr << L"\"" << std::endl;
    }
}

int executeCommand(DataStack& data)
{
    int commandNum = *(int*)data.peek(sizeof(int));
    if (isCommandNumValid(commandNum))
    {
        char* commandData = data.peek(commandDataSizeArr[commandNum]);

        int callRes = commandsArr[commandNum](AppRuntimeData, commandData);
        return callRes;
    }

    return CommandReadErrorCode;
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