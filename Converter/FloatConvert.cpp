#pragma once

#include "FloatConvert.h"

template <typename T>
CommandDataType convNum(const T& num)
{
    return (CommandDataType)(num * (T)Convert10Power);
}

template <typename T>
T deConvNum(CommandDataType num)
{
    return (T)((double)(num) / Convert10Power);
}