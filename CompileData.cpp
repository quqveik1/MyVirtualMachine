#pragma once

#include "CompileData.h"

void CompileData::put(const char* obj, int _size)
{
    size_t newSize = getData().size() + _size;
    getData().resize(newSize);

    memcpy(&getData()[currPos], obj, _size);

    currPos += _size;
}

template<typename T>
void CompileData::put(T* obj)
{
    int _size = sizeof(T);
    put((const char*)obj, _size);
}