#pragma once

#include "Processor.h"

#include "CallStack.cpp"
#include "ProcessorDebug/RuntimeInfoCollector.cpp"
#include "BreakPoint/Breakpoints.cpp"

Processor::Processor() :
    callStack(this),
    runtimeInfoCollector(*this),
    breakpoints(this)
{
};