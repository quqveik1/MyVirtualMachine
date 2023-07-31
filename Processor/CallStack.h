#pragma once

#include "../Common/StackVector.h"
#include "Processor.h"

struct CallStack : StackVector
{
    struct Processor* processor;

    CallStack(struct Processor* _processor);

    void putCurPos();

    void print();
};