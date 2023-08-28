#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "ReadCommands.h"

#include <iostream>
#include <string>
#include <queue>
#include <queue>

#include "Processor/Processor.cpp"


ErrorCode readByteCode(std::string& path, int screenX, int screenY)
{
    setlocale(LC_ALL, "russian");

    Processor processor(screenX, screenY);

    return processor.startExecutingProgramm(path);

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