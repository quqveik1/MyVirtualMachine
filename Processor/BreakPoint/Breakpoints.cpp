#pragma once

#include "Breakpoints.h"

#include "../../Constants/CommandConstants.h"

Breakpoints::Breakpoints(Processor* _processor) :
    processor(_processor)
{}

void Breakpoints::add(int pos)
{
    int originalCommand = *processor->getCommandData().get<int>(pos);
    Breakpoint bp = { pos, originalCommand, false};
    replaceWithBreakpoint(bp);

    breakPoints.push_back(bp);
}

void Breakpoints::removeEl(std::vector<Breakpoint>::iterator it)
{
    replaceWithOriginalCommand(*it);
    rewriteBreakpointPos = -1;
    breakPoints.erase(it);
}

void Breakpoints::replaceWithOriginalCommand(Breakpoint& bp)
{
    if (bp.isInCode)
    {
        processor->getCommandData().set(bp.filePos, bp.originalCommand);

        bp.isInCode = false;
    }
}

void Breakpoints::replaceWithBreakpoint(Breakpoint& bp)
{
    if (!bp.isInCode)
    {
        processor->getCommandData().set(bp.filePos, runtimeBreakPoint);
        bp.isInCode = true;
    }
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

    if (it == breakPoints.end())
    {
        return BreakPointNotFounded;
    }

    replaceWithOriginalCommand(*it);

    return WellCode;
}

ErrorCode Breakpoints::removeAllOnlyFromCode()
{
    for (int i = ((int)breakPoints.size()) - 1; i >= 0; i--)
    {
        ErrorCode res = removeByNumberOnlyFromCode(i);

        if (res != WellCode) return res;
    }

    return WellCode;
}

ErrorCode Breakpoints::removeByNumberOnlyFromCode(int num)
{
    if (!(0 <= num && num < breakPoints.size())) return BreakPointNotFounded;

    replaceWithOriginalCommand(breakPoints[num]);;

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

ErrorCode Breakpoints::insertBack(int breakNum)
{
    replaceWithBreakpoint(breakPoints[breakNum]);
    return WellCode;
}

ErrorCode Breakpoints::insertAllBack(bool needToInsertRewriteException/* = false*/)
{
    for (int i = ((int)breakPoints.size()) - 1; i >= 0; i--)
    {
        if (needToInsertRewriteException || breakPoints[i].filePos != rewriteBreakpointPos)
        {
            ErrorCode res = insertBack(i);
            if (res != WellCode) return res;
        }
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
    auto it = std::find(breakPoints.begin(), breakPoints.end(), rewriteBreakpointPos);

    if (it == breakPoints.end()) return;

    replaceWithBreakpoint(*it);

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