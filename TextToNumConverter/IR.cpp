#pragma once

#include "IR.h"

#include "CommandIR.cpp"
#include "LabelSearchIR.cpp"

IR::IR() :
    labelSearchIR(this)
{

}

CommandIR& IR::getCommand(int i) 
{ 
    return commands[i]; 
};

int IR::finishIntermediateWork()
{
    return labelSearchIR.checkLabelLinking();
}