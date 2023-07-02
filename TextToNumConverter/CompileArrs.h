#pragma once

#include "Compile1Commands.h"
#include "Compile2Commands.h"


COMMAND1COMPILETYPE commands1CompileArr[cCommands + 1]{};
COMMAND2COMPILETYPE commands2CompileArr[cCommands + 1]{};

void init1CompileArr();
void init2CompileArr();