#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <queue>

#include "..\StringSort\WStringFnc.cpp"

#include "ReadCommands.h"
#include "VMConstants.h"
#include "RuntimeData.cpp"
#include "CommandConstants.cpp"
#include "Commands.cpp"
#include "FncArrs.cpp"
#include "FileHeader.cpp"
#include "CommandConstants.cpp"
#include "Processor.cpp"


void readByteCode(std::string path)
{
    initCommandsArr();

    setlocale(LC_ALL, "ru_RU.UTF-8");

    Processor processor;

    int readRes = compiledFileWork(path, processor);

    if (readRes == WellCode)
    {
        readAndExecuteCommands(processor);
    }
    else
    {
        std::cout << "Проблема запуска скомпилированного байткода: " << readRes << std::endl;
    }
}

int compiledFileWork(std::string& path, Processor& processor)
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

    DataStack& dataStack = processor.getCommandData();

    dataStack.setSize(size);
    dataStack.setArr(new char[size]);

    fread(dataStack.getArr(), sizeof(char), size, file);

    fclose(file);

    return WellCode;
}

long fileSize(FILE* File)
{
    struct stat buff = {};
    buff.st_size = -1;

    fstat(_fileno(File), &buff);

    return buff.st_size;
}

void readAndExecuteCommands(Processor& data)
{
    int callCode = CommandReadErrorCode;

    std::queue<int> calledByteCodes;
    const size_t queueSize = 10;

    for(int i = 0; ; i++)
    {
        if(calledByteCodes.size() >= queueSize)
        {
            calledByteCodes.pop();
        }
        calledByteCodes.push(data.getCommandData().getCurrPos());

        callCode = executeCommand(data);
        if(callCode != WellCode)
        {
            break;
        }
    }

    endProgramWithCode(callCode, data, calledByteCodes);
}

void endProgramWithCode(int code, Processor& data, std::queue<int>& calledByteCodes)
{
    if(code == CommandBreakCode)
    {
        std::cout << "Программа завершилась удачно\n";
    }
    else
    {
        std::cout << "Программа неудачно завершилась с кодом: " << code << std::endl;
        if(!calledByteCodes.empty())
        {
            std::cout << "Байт коды вызываемых комманд: \n";
            for(int i = 0; !calledByteCodes.empty(); i++)
            {
                std::cout << i << ": [" << calledByteCodes.front() << "]\n";
                calledByteCodes.pop();
            }
        }
        if(data.getRuntimeData().isEmpty())
        {
            std::cout << "Стек пуст\n";
        }
        else
        {
            std::cout << "Данные в стеке:\n";
            for(int i = 0; data.getRuntimeData().isEmpty(); i++)
            {
                std::cout << i << ": [" << data.getRuntimeData().peek() << "]\n";
            }
        }
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

int executeCommand(Processor& processor)
{
    int codedCommandNum = *processor.getCommandData().peek<int>();

    int commandNum = decodeNumberRepresentation(codedCommandNum, NULL, NULL);

    if (isCommandNumValid(commandNum))
    {
        COMMANDTYPE fnc = commandsArr[commandNum];
        if (fnc)
        {
            int callRes = fnc(processor, codedCommandNum);
            return callRes;
        }
    }

    return CommandReadErrorCode;
}