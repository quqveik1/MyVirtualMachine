#pragma once
#include "Commands.cpp"
#include "TextToNumConverter/Compile1Commands.h"
#include "TextToNumConverter/Compile2Commands.h"

COMMANDTYPE commandsArr[cCommands + 1]{};
COMMAND1COMPILETYPE commands1CompileArr[cCommands + 1]{};
COMMAND2COMPILETYPE commands2CompileArr[cCommands + 1]{};

void init1CompileArr();
void init2CompileArr();
void initCommandsArr();