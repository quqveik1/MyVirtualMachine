#pragma once

#include "Breakpoints.h"

#include "../../Constants/CommandConstants.h"

Breakpoints::Breakpoints(Processor* _processor) :
    processor(_processor)
{}

void Breakpoints::add(int pos)
{
    int originalCommand = *processor->getCommandData().get<int>(pos);
    Breakpoint bp = { pos, originalCommand };
    processor->getCommandData().set(pos, breakpoint_num);
    

    breakPoints.push_back(bp);
}

ErrorCode Breakpoints::remove(int pos)
{
    bool hasOriginalCodeChanged = false;
    for (;;)
    {
        auto it = std::find(breakPoints.begin(), breakPoints.end(), pos);

        if (it == breakPoints.end()) break;

        processor->getCommandData().set(pos, it->originalCommand);
        hasOriginalCodeChanged = true;

        breakPoints.erase(it);
    }

    if(!hasOriginalCodeChanged)
    {
        return BreakPointNotFounded;
    }

    return WellCode;

}

bool Breakpoints::needToRewriteBreakpoint()
{
    if(rewriteBreakpointPos >= 0 ) return true;
    return false;
}

void Breakpoints::rewriteBreakpoint()
{
    add(rewriteBreakpointPos);
    rewriteBreakpointPos = -1;
}

void Breakpoints::setRewriteBreakpoint(int pos)
{
    rewriteBreakpointPos = pos;
}

void Breakpoints::observeBreakpoints()
{
    if(needToRewriteBreakpoint())
    {
        rewriteBreakpoint();
    }
}