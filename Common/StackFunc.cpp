#pragma once

#include "StackFunc.h"

#include <exception>

template <typename T>
T _peek(std::stack<T>& s)
{
    T top = s.top();
    s.pop();
    return top;
}

