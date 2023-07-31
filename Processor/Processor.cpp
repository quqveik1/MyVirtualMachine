#pragma once

#include "Processor.h"

#include "CallStack.cpp"
#include "ProcessorDebug\RuntimeInfoCollector.cpp"

Processor::Processor() :
    callStack(this),
    runtimeInfoCollector(*this)
{
};