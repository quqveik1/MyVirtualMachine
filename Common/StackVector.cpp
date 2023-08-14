#pragma once

#include "StackVector.h"

std::vector<int>& StackVector::getData()
{
    return data;
}

int StackVector::peek()
{
    int ans = get();

    getData().pop_back();

    return ans;
}

void StackVector::pop()
{
    if(getData().size() == 0)
    {
        throw std::runtime_error("Нельзя удаляться из пустого стека");
        return;
    }
    getData().pop_back();
}

int StackVector::get()
{
    if (getData().empty())
    {
        throw std::runtime_error("Нельзя удаляться из пустого стека");
        return {};
    }
    return getData().back();
}

void StackVector::push(int obj)
{
    return getData().push_back(obj);
}

int* StackVector::at(int pos)
{
    if (0 <= pos && pos < getData().size())
    {
        return &(getData()[pos]);
    }
    return nullptr;
}