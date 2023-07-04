#pragma once

#include "Processor.h"

#include "CallStack.cpp"

Processor::Processor() :
    callStack(this)
{
};