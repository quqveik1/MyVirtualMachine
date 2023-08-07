#pragma once
#include "Commands.cpp"

COMMANDTYPE commandsArr[cCommands + 1]{};

void initCommandsArr();

COMMANDTYPE getCommand(int num);