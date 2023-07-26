#pragma once

#include "DisassemblerArrs.h"

void initDisassemblerCommands()
{
    disassemblerCommands[push_num] = defaultSmallExpression_dissassemblerCommand;
    disassemblerCommands[pop_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[out_num] = hexSaveSmallExpression_dissassemblerCommand;

    disassemblerCommands[push_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[pop_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[jmp_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[ja_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[jae_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[jb_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[jbe_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[je_num] = hexSaveSmallExpression_dissassemblerCommand;
    disassemblerCommands[jne_num] = hexSaveSmallExpression_dissassemblerCommand;

    disassemblerCommands[call_num] = hexSaveSmallExpression_dissassemblerCommand;
}