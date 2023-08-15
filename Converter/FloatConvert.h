#pragma once

#include "../Constants/CommandConstants.h"

const long long Convert10Power = 65536;

template <typename T>
CommandDataType convNum(const T& num);

template <typename T>
T deConvNum(CommandDataType num);