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
    void replaceWithOriginalCommand(Breakpoint& bp);
    void replaceWithBreakpoint(Breakpoint& bp);

public:
    Breakpoints(Processor* _processor);

    void add(int pos);
    ErrorCode remove(int pos);
    ErrorCode removeOnlyFromCode(int pos);
    ErrorCode removeAllOnlyFromCode();
    ErrorCode removeByNumber(int num);
    ErrorCode removeByNumberOnlyFromCode(int num);
    ErrorCode removeAll();

    ErrorCode insertBack(int breakNum);
    ErrorCode insertAllBack(bool needToInsertRewriteException = false);

    bool needToRewriteBreakpoint();
    void rewriteBreakpoint();
    void setRewriteBreakpoint(int pos);
    void observeBreakpoints();

    ErrorCode print();
};