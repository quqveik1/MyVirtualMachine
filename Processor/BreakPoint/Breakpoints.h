#pragma once

#include <vector>

#include "Breakpoint.h"
#include "../Processor.h"

class Breakpoints
{
    std::vector<Breakpoint> breakPoints;
    Processor* processor;
    int rewriteBreakpointPos = -1;

    void removeEl(std::vector<Breakpoint>::iterator it);
    void changeCodeForEl(std::vector<Breakpoint>::iterator it);

public:
    Breakpoints(Processor* _processor);

    void add(int pos);
    ErrorCode remove(int pos);
    ErrorCode removeOnlyFromCode(int pos);
    ErrorCode removeByNumber(int num);
    ErrorCode removeAll();

    bool needToRewriteBreakpoint();
    void rewriteBreakpoint();
    void setRewriteBreakpoint(int pos);
    void observeBreakpoints();

    ErrorCode print();
};