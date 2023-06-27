#pragma once

#include "StackFunc.h"

#include <exception>

template <typename T>
T _peek(std::stack<T>& s)
{
    if (s.empty())
    {
        throw std::runtime_error( "Попытка взять из пустого стека элемент\n");
        return {};
    }

    T top = s.top();
    s.pop();
    return top;
}

