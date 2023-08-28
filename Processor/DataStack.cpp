#pragma once

#include "DataStack.h"
#include "../Common/CommonCode.cpp"

char* DataStack::peek(int _size)
{
    int retPos = currPos;
    if (_size == 0) return NULL;
    currPos += _size;
    if (currPos <= size)
    {
        return &arr[retPos];
    }
    else
    {
        throw std::exception("peek: currPos > size");
    }
    return NULL;
}

char* DataStack::get(int _size, int pos)
{
    if (pos < 0) pos = currPos;
    if (pos + _size < size)
    {
        return &arr[pos];
    }
    else
    {
        throw std::exception("peek: currPos > size");
    }
    return NULL;
}

void DataStack::set(int pos, int _size, char* data)
{
    memcpy(&(getArr()[pos]), data, _size);
}

template<typename T>
void DataStack::set(int pos, T data)
{
    set(pos, sizeof(T), (char*)&data);
}

template<typename T>
T* DataStack::peek()
{
    int _size = sizeof(T);
    return (T*)peek(_size);
}

template<typename T>
T* DataStack::get(int pos/* = -1*/)
{
    int _size = sizeof(T);
    return (T*)get(_size, pos);
}

bool DataStack::setCurrPos(int _pos)
{
    if(checkArrBound(getSize(), _pos))
    {
        currPos = _pos;
        return true;
    }
    return false;
}

bool DataStack::moveCursor(int _delta)
{
    if(_delta == 0)
    {
        std::cout << "Zero offset moveCursor\n";
    }
    return setCurrPos(getCurrPos() + _delta);
}

template<typename T>
bool DataStack::moveCursor()
{
    return moveCursor(sizeof(T));
}