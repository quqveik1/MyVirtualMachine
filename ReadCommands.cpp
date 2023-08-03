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

ErrorCode readByteCode(std::string path)
{
    initCommandsArr();

    setlocale(LC_ALL, "ru_RU.UTF-8");

    Processor processor;

    return processor.startExecutingProgramm(path);

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