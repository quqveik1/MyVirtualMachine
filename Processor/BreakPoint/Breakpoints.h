#pragma once

#include <vector>

#include "Breakpoint.h"
#include "../Processor.h"

class Breakpoints
{
    std::vector<Breakpoint> breakPoints;
    Processor* processor;
    int rewriteBreakpointPos = -1;
public:
    Breakpoints(Processor* _processor);

    void add(int pos);
    ErrorCode remove(int pos);

    bool needToRewriteBreakpoint();
    void rewriteBreakpoint();
    void setRewriteBreakpoint(int pos);
    void observeBreakpoints();
};