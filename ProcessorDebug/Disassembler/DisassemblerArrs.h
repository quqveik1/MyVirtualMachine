#pragma once

#include "DisassemblerCommands.h"

#include "../../Constants/CommandConstants.h"

DISASSEMBLERCOMMANDS disassemblerCommands[cCommands + 1]{};

void initDisassemblerCommands();

DISASSEMBLERCOMMANDS getDisassemblerCommand(int num);