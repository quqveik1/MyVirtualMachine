#pragma once

#include "StackFunc.h"

#include <exception>

template <typename T>
T _peek(std::stack<T>& s)
{
    if (s.empty())
    {
        throw std::runtime_error( "������� ����� �� ������� ����� �������\n");
        return {};
    }

    T top = s.top();
    s.pop();
    return top;
}

