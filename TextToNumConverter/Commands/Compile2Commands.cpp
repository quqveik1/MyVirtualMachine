#pragma once

#include "Compile2Commands.h"

#include <string>
#include <string_view>

#include "../../Constants/CommandConstants.h"
#include "IR/IR.h"
#include "Bin/BinCompileData.h"

ErrorCode default_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    if (commandIR.getData().size() > 0)
    {
        binCompileData.put(&commandIR.getData()[0], (int)commandIR.getData().size());
    }
    return ErrorCode::WellCode;
}

ErrorCode saveWordExpressionToBin(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    binCompileData.put(&commandIR.getData()[0], sizeof(int));

    //std::wstring_view word = (wchar_t*)commandIR.getCommandData();
    binCompileData.getLabelSearchBin().writeOrWaitLabel(commandIR.getLabelLinePos());

    return ErrorCode::WellCode;
}

ErrorCode optional_word_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
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

ErrorCode out_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    return optional_word_2compile(commandIR, ir, binCompileData);
}

ErrorCode jmp_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    return optional_word_2compile(commandIR, ir, binCompileData);
}

ErrorCode word_2compile(CommandIR& commandIR, IR& ir, BinCompileData& binCompileData)
{
    binCompileData.getLabelSearchBin().pushWord(commandIR.getLabelLinePos());

    return ErrorCode::WellCode;
}