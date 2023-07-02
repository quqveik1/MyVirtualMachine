#pragma once

#include "CompileArrs.h"

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

    commands1CompileArr[word_num] = word_1compile;
}

void init2CompileArr()
{
    commands2CompileArr[out_num] = out_2compile;

    commands2CompileArr[jmp_num] = jmp_2compile;
    commands2CompileArr[ja_num] = jmp_2compile;
    commands2CompileArr[jae_num] = jmp_2compile;
    commands2CompileArr[jb_num] = jmp_2compile;
    commands2CompileArr[jbe_num] = jmp_2compile;
    commands2CompileArr[je_num] = jmp_2compile;
    commands2CompileArr[jne_num] = jmp_2compile;

    commands2CompileArr[word_num] = word_2compile;
}