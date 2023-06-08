#pragma once

#include "FncArrs.h"

#include "TextToNumConverter/CompileCommands.cpp"

void initCompileArr()
{
    commandsCompileArr[in_num] = default_compile;
    commandsCompileArr[out_num] = default_compile;
    commandsCompileArr[push_num] = push_compile;
    commandsCompileArr[hlt_num] = default_compile;
    commandsCompileArr[add_num] = default_compile;
    commandsCompileArr[sub_num] = default_compile;
    commandsCompileArr[mul_num] = default_compile;
    commandsCompileArr[div_num] = default_compile;
    commandsCompileArr[pop_num] = pop_compile;
    commandsCompileArr[jmp_num] = jmp_compile;
    commandsCompileArr[ja_num] = jmp_compile;
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
    commandsArr[pop_num] = pop_command;
    commandsArr[jmp_num] = jmp_command;
    commandsArr[ja_num] = ja_command;
}