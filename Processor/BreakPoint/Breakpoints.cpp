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

void Breakpoints::removeEl(std::vector<Breakpoint>::iterator it)
{
    changeCodeForEl(it);
    rewriteBreakpointPos = -1;
    breakPoints.erase(it);
}

void Breakpoints::changeCodeForEl(std::vector<Breakpoint>::iterator it)
{
    processor->getCommandData().set(it->filePos, it->originalCommand);
}

ErrorCode Breakpoints::remove(int pos)
{
    auto it = std::find(breakPoints.begin(), breakPoints.end(), pos);

    if (it == breakPoints.end()) return BreakPointNotFounded;

    removeEl(it);

    return WellCode;

}

ErrorCode Breakpoints::removeOnlyFromCode(int pos)
{
    auto it = std::find(breakPoints.begin(), breakPoints.end(), pos);

    if (it == breakPoints.end()) return BreakPointNotFounded;

    changeCodeForEl(it);

    return WellCode;
}

ErrorCode Breakpoints::removeByNumber(int num)
{
    if (!(0 <= num && num < breakPoints.size())) return BreakPointNotFounded;

    removeEl(breakPoints.begin() + num);

    return WellCode;
}

ErrorCode Breakpoints::removeAll()
{
    for(int i = ((int)breakPoints.size()) - 1; i >= 0; i--)
    {
        ErrorCode res = removeByNumber(i);

        if (res != WellCode) return res;
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

ErrorCode Breakpoints::print()
{
    if(breakPoints.size() == 0)
    {
        std::cout << "Точек остановки нет\n";
    }

    for (int i = 0; i < breakPoints.size(); i++)
    {
        std::cout << std::setfill('0') << std::setw(5) << std::right << std::dec << i << " | "
             << std::setfill('0') << std::setw(5) << std::right << std::hex << breakPoints[i].filePos << "\n";
    }

    return WellCode;
}