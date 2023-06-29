#pragma once

#include "BufferObj.h"

void BufferObj::put(const char* obj, int _size)
{
    size_t newSize = getData().size() + _size;
    getData().resize(newSize);

    memcpy(&getData()[currPos], obj, _size);

    currPos += _size;
}

void BufferObj::change(const char* obj, int _size, int pos)
{
    memcpy(&getData()[pos], obj, _size);
}

template<typename T>
void BufferObj::put(T* obj)
{
    int _size = sizeof(T);
    put((const char*)obj, _size);
}

template<typename T>
void BufferObj::put(T& obj)
{
    int _size = sizeof(T);
    put((const char*)(&obj), _size);
}

template<typename T>
void BufferObj::change(T& obj, int pos)
{
    int _size = sizeof(T);
    change((const char*)(&obj), _size, pos);
}