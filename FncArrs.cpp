#pragma once

#include "FncArrs.h"

#include "CompileCommands.cpp"


void initSizeArr()
{
    commandDataSizeArr[in_num] = 0;
    commandDataSizeArr[out_num] = 0;
    commandDataSizeArr[push_num] = (int)sizeof(int);
    commandDataSizeArr[hlt_num] = 0;
    commandDataSizeArr[add_num] = 0;
    commandDataSizeArr[sub_num] = 0;
    commandDataSizeArr[mul_num] = 0;
    commandDataSizeArr[div_num] = 0;
}  

void initCompileArr()
{
    commandsCompileArr[in_num] = 0;
    commandsCompileArr[out_num] = 0;
    commandsCompileArr[push_num] = push_compile;
    commandsCompileArr[hlt_num] = 0;
    commandsCompileArr[add_num] = 0;
    commandsCompileArr[sub_num] = 0;
    commandsCompileArr[mul_num] = 0;
    commandsCompileArr[div_num] = 0;
}

void initCommandsArr()
{
    commandsArr[in_num] = in_command;
    commandsArr[out_num] = out_command;
    commandsArr[push_num] = push_command;
    commandsArr[hlt_num] = hlt_command;
    commandsArr[add_num] = add_command;
    commandsArr[sub_num] = sub_command;
    commandsArr[mul_num] = mul_command;
    commandsArr[div_num] = div_command;
}