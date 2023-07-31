#pragma once

#include "Compile2Commands.h"

#include <string>
#include <string_view>

#include "../../Constants/CommandConstants.h"
#include "IR/IR.h"
#include "Bin/BinCompileData.h"

int default_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    if (commandIR.getData().size() > 0)
    {
        binCompileData.put(&commandIR.getData()[0], (int)commandIR.getData().size());
    }
    return WellCode;
}

int saveWordExpressionToBin(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    binCompileData.put(&commandIR.getData()[0], sizeof(int));

    //std::wstring_view word = (wchar_t*)commandIR.getCommandData();
    binCompileData.getLabelSearchBin().writeOrWaitLabel(commandIR.getLabelLinePos());

    return WellCode;
}

int out_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    if (commandIR.getHasLabel())
    {
        return saveWordExpressionToBin(commandIR, ir, binCompileData);
    }
    else
    {
        return default_2compile(commandIR, ir, binCompileData);
    }
}

int jmp_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    if(commandIR.getHasLabel())
    {
        return saveWordExpressionToBin(commandIR, ir, binCompileData);
    }
    else
    {
        return default_2compile(commandIR, ir, binCompileData);
    }
}


int word_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    //std::wstring_view word = (wchar_t*)commandIR.getCommandData();

    binCompileData.getLabelSearchBin().pushWord(commandIR.getLabelLinePos());

    return WellCode;
}