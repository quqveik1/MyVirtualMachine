
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
#include "FncArrs.cpp"
#include "FileHeader.cpp"


void readByteCode(std::string path)
{
    initCommandsArr();
    initSizeArr();

    setlocale(LC_ALL, "ru_RU.UTF-8");

    DataStack dataStack;

    int readRes = compiledFileWork(path, dataStack);

    if (readRes == WellCode)
    {
        readAndExecuteCommands(dataStack);
    }
}

int compiledFileWork(std::string& path, DataStack& dataStack)
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

    dataStack.setSize(size);
    dataStack.setArr(new char[size]);

    fread(dataStack.getArr(), sizeof(char), size, file);

    fclose(file);
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

/*
push 15    //команда для чисел
pop ax   

// после компиляции

4 15
9 1

//число ax = 15

//конец

push ax
push 1
add
pop ax

// после компиляции

10 1
4 1
5
9 1

//число на 1 больше
*/

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