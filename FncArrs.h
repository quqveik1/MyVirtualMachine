#pragma once
#include "Commands.cpp"
#include "TextToNumConverter/Compile1Commands.h"

COMMANDTYPE commandsArr[cCommands + 1]{};
COMMAND1COMPILETYPE commands1CompileArr[cCommands + 1]{};

void initCompileArr();
void initCommandsArr();