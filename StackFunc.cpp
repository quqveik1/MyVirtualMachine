//
// Created by Kurlic on 11.05.2023.
//

#include "StackFunc.h"

template <typename T>
T _peek(std::stack<T>& s)
{
    if (s.empty())
    {
        std::cout << "������� ����� �� ������� ����� �������\n";
        return {};
    }

    T top = s.top();
    s.pop();
    return top;
}

