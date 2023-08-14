#pragma once

#include "../IR/IR.h"
#include "../Bin/BinCompileData.h"
#include "../Constants/ErrorCode.h"

using COMMAND2COMPILETYPE = 
ErrorCode (*)                            (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

ErrorCode default_2compile               (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

ErrorCode out_2compile                   (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

ErrorCode saveWordExpressionToBin        (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);

ErrorCode jmp_2compile                   (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);
ErrorCode word_2compile                  (CommandIR& commandIR, IR& ir, BinCompileData& binCompileData);
