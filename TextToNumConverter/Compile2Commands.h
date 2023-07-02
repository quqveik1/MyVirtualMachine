#pragma once

#include "CommandIR.h"
#include "IR.h"
#include "BinCompileData.h"

using COMMAND2COMPILETYPE = int (*)(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

int default_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

int out_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

int saveWordExpressionToBin(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

int jmp_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);
int word_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);
