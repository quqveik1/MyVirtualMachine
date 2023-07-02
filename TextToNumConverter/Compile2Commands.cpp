#pragma once

#include "Compile2Commands.h"

#include <string>
#include <string_view>

#include "../CommandConstants.h"
#include "IR.h"
#include "BinCompileData.h"

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

    std::wstring_view word = (wchar_t*)commandIR.getCommandData();
    binCompileData.getWordSearch().writeOrWaitWord(word);

    return WellCode;
}

int out_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    if (commandIR.getHasWord())
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
    if(commandIR.getHasWord())
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
    std::wstring_view word = (wchar_t*)commandIR.getCommandData();

    binCompileData.getWordSearch().pushWord(word);

    return WellCode;
}