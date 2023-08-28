#pragma once

#include "Stack.h"

#include "StackFunc.cpp"

std::stack<int>& Stack::getData()
{
    return data;
}


int Stack::peek()
{
    return _peek(getData());
}

int Stack::get()
{
    if (getData().empty())
    {
        std::cout << "Attempt to take from an empty stack\n";
        return {};
    }
    return getData().top();
}

void Stack::push(int obj)
{
    return getData().push(obj);
}