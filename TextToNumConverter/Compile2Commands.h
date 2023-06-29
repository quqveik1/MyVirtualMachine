#pragma once

#include "CommandIR.h"
#include "IR.h"
#include "BinCompileData.h"

using COMMAND2COMPILETYPE = int (*)(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

int default_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);