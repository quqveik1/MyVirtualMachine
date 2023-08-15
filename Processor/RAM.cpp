#pragma once

#include "RAM.h"

#include <exception>

#include "../Common/CommonCode.cpp"
#include "../Common/StringViewExtension.cpp"
#include "../Converter/FloatConvert.h"

CommandDataType& RAM::operator[](CommandDataType index)
{
    if (!checkArrBound(arrSize, index))
    {
        throw std::exception("Out of range");
        return data[0];
    }

    return data[index];
}

void RAM::print(CommandDataType index)
{
    CommandDataType& data = (*this)[index];

    CommandDataFloatType deconvData = deConvNum<CommandDataFloatType>(data);

    std::cout << std::setw(3) << std::setfill('0') << std::right << std::hex << index << ": " << std::dec << deconvData << "\n";
}

CommandDataType RAM::getPixel(CommandDataType x, CommandDataType y)
{
    CommandDataType index = y * xSize + x + arrSize;

    if (!checkArrBound(VRAMSize, index))
    {
        return 0;
    }

    return data[index];
}

void RAM::setPixel(CommandDataType x, CommandDataType y, CommandDataType pix)
{
    CommandDataType index = y * xSize + x + arrSize;

    if (!checkArrBound(VRAMSize, index))
    {
        return;
    }

    data[index] = pix;
}