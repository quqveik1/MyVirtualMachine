#pragma once

#include "CallStack.h"

#include "Processor.h"
#include "../Common/StackVector.cpp"

CallStack::CallStack(struct Processor* _processor) :
    processor(_processor)
{
}

void CallStack::putCurPos()
{
    if (!processor)
    {
        throw std::runtime_error("CallStack has no access to processor");
        return;
    }

    push(processor->getCommandData().getCurrPos());
}

void CallStack::print()
{
    if (getData().empty())
    {
        std::cout << "Стек вызовов пуст" << std::endl;

        return;
    }

    std::cout << "Стек вызовов с начала до конца: \n";

    for (size_t i = 0; i < getData().size(); i++)
    {
        int data = getData()[i];

        std::cout << std::setw(5) << std::setfill('0') << std::right << std::dec << i << ": " << std::hex << data << std::endl;
    }

    std::cout << std::dec << "Конец стека вызовов\n";
}