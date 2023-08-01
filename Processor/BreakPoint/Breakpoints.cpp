#pragma once

#include "Breakpoints.h"

#include "../../Constants/CommandConstants.h"

Breakpoints::Breakpoints(Processor* _processor) :
    processor(_processor)
{}

void Breakpoints::add(int pos)
{
    int originalCommand = *processor->getCommandData().get(pos);
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