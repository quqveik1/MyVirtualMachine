#pragma once

const int FloatPrecise = 4;
const int Convert10Power = 10000;

template <typename T>
int convNum(const T& num);

template <typename T>
T deConvNum(int num);