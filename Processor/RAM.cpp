#pragma once

#include "RAM.h"

#include <exception>

#include "../Common/CommonCode.cpp"
#include "../Common/StringViewExtension.cpp"
#include "../Converter/FloatConvert.h"

int& RAM::operator[](int index)
{
    if (!checkArrBound(arrSize, index))
    {
        throw std::exception("Out of range");
        return data[0];
    }

    return data[index];
}

void RAM::print(int index)
{
    int& data = (*this)[index];

    float deconvData = deConvNum<float>(data);

    std::cout << std::setw(3) << std::setfill('0') << std::right << std::hex << index << ": " << std::dec << deconvData << "\n";
}

int RAM::getPixel(int x, int y)
{
    int index = y * xSize + x;

    return data[index];
}

void RAM::setPixel(int x, int y, int pix)
{
    int index = y * xSize + x;

    data[index] = pix;
}