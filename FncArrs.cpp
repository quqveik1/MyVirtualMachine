#pragma once

#include "FncArrs.h"

#include "TextToNumConverter/Compile1Commands.cpp"

void init1CompileArr()
{
    commands1CompileArr[in_num] = default_1compile;
    commands1CompileArr[out_num] = out_1compile;

    commands1CompileArr[push_num] = push_1compile;

    commands1CompileArr[hlt_num] = default_1compile;

    commands1CompileArr[add_num] = default_1compile;
    commands1CompileArr[sub_num] = default_1compile;
    commands1CompileArr[mul_num] = default_1compile;
    commands1CompileArr[div_num] = default_1compile;

    commands1CompileArr[pop_num] = pop_1compile;

    commands1CompileArr[jmp_num] = jmp_1compile;
    commands1CompileArr[ja_num] = jmp_1compile;
    commands1CompileArr[jae_num] = jmp_1compile;
    commands1CompileArr[jb_num] = jmp_1compile;
    commands1CompileArr[jbe_num] = jmp_1compile;
    commands1CompileArr[je_num] = jmp_1compile;
    commands1CompileArr[jne_num] = jmp_1compile;

    commands1CompileArr[sqrt_num] = default_1compile;

    commands1CompileArr[db_num] = db_1compile;
}

void init2CompileArr()
{
    
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
    commandsArr[jae_num] = jae_command;
    commandsArr[jb_num] = jb_command;
    commandsArr[jbe_num] = jbe_command;
    commandsArr[je_num] = je_command;
    commandsArr[jne_num] = jne_command;
    commandsArr[sqrt_num] = sqrt_command;
}