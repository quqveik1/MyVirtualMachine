#pragma once

#include "IR.h"

#include "CommandIR.cpp"

IR::IR()
{

}

CommandIR& IR::getCommand(int i) 
{ 
    return commands[i]; 
};