#pragma once

#include "ByteConverter.h"

int codeToNumberRepresentation(int num, bool hasConstant, bool hasRegister)
{
    if (hasConstant)
    {
        num |= 1 << 4;
    }  
    if (hasRegister)
    {
        num |= 1 << 5;
    }

    return num;
}

int decodeNumberRepresentation(int codeNum, bool* hasConstant, bool* hasRegister)
{
    int answer = codeNum;
    if (hasConstant) *hasConstant = (bool((1 << 4) & codeNum));
    if (hasRegister) *hasRegister = (bool((1 << 5) & codeNum));

    answer &= ~(1 << 4);
    answer &= ~(1 << 5);

    return answer;
}

const int regDataPos = 8 * 4 - 1;

int codeToDataRepr(int data, bool isRegister)
{
    if (isRegister)
    {
        data |= 1 << regDataPos;
    }

    return data;
}

int decodeDataRepr(int data, bool* isRegister)
{
    if (isRegister) *isRegister = (bool((1 << regDataPos) & data));

    data &= ~(1 << regDataPos);

    return data;
}