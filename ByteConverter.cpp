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
    *hasConstant = (bool((1 << 4) & codeNum));
    *hasRegister = (bool((1 << 5) & codeNum));

    answer &= ~(1 << 4);
    answer &= ~(1 << 5);

    return answer;
}