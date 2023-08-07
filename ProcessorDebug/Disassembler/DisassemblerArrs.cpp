#pragma once

#include "DisassemblerArrs.h"

void initDisassemblerCommands()
{
    disassemblerCommands[push_num] = defaultSmallExpression_dissassemblerCommand;
    disassemblerCommands[pop_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[out_num] = hexSaveSmallExpression_dissassemblerCommand;

    disassemblerCommands[push_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[pop_num] = defaultSmallExpression_dissassemblerCommand;

    disassemblerCommands[jmp_num] = jmp_dissassemblerCommand;
    disassemblerCommands[ja_num] = jmp_dissassemblerCommand;
    disassemblerCommands[jae_num] = jmp_dissassemblerCommand;
    disassemblerCommands[jb_num] = jmp_dissassemblerCommand;
    disassemblerCommands[jbe_num] = jmp_dissassemblerCommand;
    disassemblerCommands[je_num] = jmp_dissassemblerCommand;
    disassemblerCommands[jne_num] = jmp_dissassemblerCommand;

    disassemblerCommands[ret_num] = ret_dissassemblerCommand;
    disassemblerCommands[call_num] = jmp_dissassemblerCommand;

    disassemblerCommands[si_num] = si_dissassemblerCommand;
}

DISASSEMBLERCOMMANDS getDisassemblerCommand(int num)
{
    return disassemblerCommands[num];
}