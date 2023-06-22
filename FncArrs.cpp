#pragma once

#include "FncArrs.h"

#include "TextToNumConverter/CompileCommands.cpp"

void initCompileArr()
{
    commandsCompileArr[in_num] = default_compile;
    commandsCompileArr[out_num] = out_compile;

    commandsCompileArr[push_num] = push_compile;

    commandsCompileArr[hlt_num] = default_compile;

    commandsCompileArr[add_num] = default_compile;
    commandsCompileArr[sub_num] = default_compile;
    commandsCompileArr[mul_num] = default_compile;
    commandsCompileArr[div_num] = default_compile;

    commandsCompileArr[pop_num] = pop_compile;

    commandsCompileArr[jmp_num] = jmp_compile;
    commandsCompileArr[ja_num] = jmp_compile;
    commandsCompileArr[jae_num] = jmp_compile;
    commandsCompileArr[jb_num] = jmp_compile;
    commandsCompileArr[jbe_num] = jmp_compile;
    commandsCompileArr[je_num] = jmp_compile;
    commandsCompileArr[jne_num] = jmp_compile;

    commandsCompileArr[sqrt_num] = default_compile;

    commandsCompileArr[db_num] = db_compile;
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


void initCommandsListingArr()
{
        
}