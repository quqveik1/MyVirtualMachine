#pragma once

#include "RAM.h"

#include <exception>

#include "CommonCode.cpp"

int& RAM::operator[](int index)
{
    if (!checkArrBound(arrSize, index))
    {
        throw std::exception("Out of range");
        return data[0];
    }

    return data[index];
}