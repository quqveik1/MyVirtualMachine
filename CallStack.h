#pragma once

#include "Stack.h"
#include "Processor.h"

struct CallStack : Stack
{
    struct Processor* processor;

    CallStack(struct Processor* _processor);

    void putCurPos();
};