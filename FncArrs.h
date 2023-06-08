#pragma once
#include "Commands.cpp"
#include "TextToNumConverter/CompileCommands.h"

COMMANDTYPE commandsArr[cCommands + 1]{};
int commandDataSizeArr[cCommands + 1]{};
COMMANDCOMPILETYPE commandsCompileArr[cCommands + 1]{};

void initSizeArr();
void initCompileArr();
void initCommandsArr();