#pragma once

#include "../Common/Stack.h"
#include "Processor.h"

struct CallStack : Stack
{
    struct Processor* processor;

    CallStack(struct Processor* _processor);

    void putCurPos();
};