#pragma once

#include <vector>

#include "Breakpoint.h"
#include "../Processor.h"

class Breakpoints
{
    std::vector<Breakpoint> breakPoints;
    Processor* processor;
public:
    Breakpoints(Processor* _processor);

    void add(int pos);
    ErrorCode remove(int pos);
};