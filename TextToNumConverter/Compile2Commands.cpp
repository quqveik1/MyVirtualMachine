#pragma once

#include "Compile2Commands.h"

#include "../CommandConstants.h"
#include "IR.h"
#include "BinCompileData.h"

int default_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    binCompileData.put(&commandIR.getData()[0], (int)commandIR.getData().size());
    return WellCode;
}