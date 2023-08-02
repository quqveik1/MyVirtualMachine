#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <queue>

#include "..\StringSort\WStringFnc.cpp"

#include "ReadCommands.h"
#include "Constants/VMConstants.h"
#include "Constants/CommandConstants.cpp"
#include "Commands.cpp"
#include "Constants/FncArrs.cpp"
#include "FileHeader.cpp"
#include "Processor/Processor.cpp"
#include "InteractiveMode/InteractiveMode.cpp"

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


/** File pos  |  Command pos  |  Command                 | Disassembly
 *  000172    |  0004         |  00 00 00 00 00 00 00 00 | push 5
 */

void readAndExecuteCommands(Processor& data)
{
    int callCode = CommandReadErrorCode;

    for(int i = 0; ; i++)
    {
        callCode = executeCommand(data);
        if(callCode != WellCode)
        {
            break;
        }
    }

    endProgramWithCode(callCode, data);
}

void endProgramWithCode(int code, Processor& processor)
{
    if(code == CommandBreakCode)
    {
        std::cout << "\nПрограмма завершилась удачно\n";
    }
    else
    {
        InteractiveCode interCode = ContinueInteractiveMode;
        startInteractiveMode(processor, (ErrorCode)code, interCode);
        if(interCode == ContinueAppExecuting)
        {
            readAndExecuteCommands(processor);
        }
    }
}

void printCallStack()
{
    
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
    int filePos = processor.getCommandData().getCurrPos();

    int codedCommandNum = *processor.getCommandData().peek<int>();
    processor.getBreakpoints().observeBreakpoints();


    int commandNum = decodeNumberRepresentation(codedCommandNum, NULL, NULL);

    if (isCommandNumValid(commandNum))
    {
        COMMANDTYPE fnc = commandsArr[commandNum];
        if (fnc)
        {
            int callRes = fnc(processor, codedCommandNum);

            processor.getRuntimeInfoCollector().addLastCommand(filePos, commandNum);

            return callRes;
        }
    }

    return CommandReadErrorCode;
}