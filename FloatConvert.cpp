#pragma once

#include "FloatConvert.h"

template <typename T>
int convNum(const T& num)
{
    return (T)num * Convert10Power;
}