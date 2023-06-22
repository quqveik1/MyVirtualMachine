#pragma once
#include "Commands.cpp"
#include "TextToNumConverter/CompileCommands.h"
#include "ListCommands.h"

COMMANDTYPE commandsArr[cCommands + 1]{};
COMMANDCOMPILETYPE commandsCompileArr[cCommands + 1]{};
COMMANDLISTINGTYPE commandsListingArr[cCommands + 1]{};

void initCompileArr();
void initCommandsArr();
void initCommandsListingArr();