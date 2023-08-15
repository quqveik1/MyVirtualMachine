#pragma once

#include "../Common/StackVector.h"
#include "Processor.h"

struct CallStack : StackVector<CommandDataType>
{
    struct Processor* processor;

    CallStack(struct Processor* _processor);

    void putCurPos();

    void print();
};