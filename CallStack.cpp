#pragma once

#include "CallStack.h"

#include "Processor.h"
#include "Stack.cpp"

CallStack::CallStack(struct Processor* _processor) :
    processor(_processor)
{
}

void CallStack::putCurPos()
{
    if (!processor)
    {
        throw std::runtime_error("CallStack has no access to proessor");
        return;
    }

    push(processor->getCommandData().getCurrPos());
}