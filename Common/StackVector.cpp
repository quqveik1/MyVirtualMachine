#pragma once

#include "StackVector.h"

template<typename T>
std::vector<T>& StackVector<T>::getData()
{
    return data;
}

template<typename T>
T StackVector<T>::peek()
{
    CommandDataType ans = get();

    getData().pop_back();

    return ans;
}

template<typename T>
void StackVector<T>::pop()
{
    if(getData().size() == 0)
    {
        throw std::runtime_error("Нельзя удаляться из пустого стека");
        return;
    }
    getData().pop_back();
}

template<typename T>
T StackVector<T>::get()
{
    if (getData().empty())
    {
        throw std::runtime_error("Нельзя удаляться из пустого стека");
        return {};
    }
    return getData().back();
}

template<typename T>
void StackVector<T>::push(T obj)
{
    return getData().push_back(obj);
}

template<typename T>
T* StackVector<T>::at(int pos)
{
    if (0 <= pos && pos < getData().size())
    {
        return &(getData()[pos]);
    }
    return nullptr;
}