//
// Created by Kurlic on 11.05.2023.
//

#include "StackFunc.h"

#include <exception>

template <typename T>
T _peek(std::stack<T>& s)
{
    if (s.empty())
    {
        throw std::exception( "Попытка взять из пустого стека элемент\n");
        return {};
    }

    T top = s.top();
    s.pop();
    return top;
}

