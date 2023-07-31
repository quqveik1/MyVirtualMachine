#pragma once

#include "FloatConvert.h"

template <typename T>
int convNum(const T& num)
{
    return (int)(num * (T)Convert10Power);
}

template <typename T>
T deConvNum(int num)
{
    return ((T)num) / Convert10Power;
}