#pragma once

#include "StackVector.h"

std::vector<int>& StackVector::getData()
{
    return data;
}

int StackVector::peek()
{
    int ans = getData().back();

    getData().pop_back();

    return ans;
}

int StackVector::get()
{
    if (getData().empty())
    {
        std::cout << "Попытка взять из пустого стека элемент\n";
        return {};
    }
    return getData().back();
}

void StackVector::push(int obj)
{
    return getData().push_back(obj);
}