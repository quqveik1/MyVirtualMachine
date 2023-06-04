#pragma once

#include "ByteConverter.h"

const int constBitMove = 4;
const int regBitMove = 5;
const int ramBitMove = 6;

int codeToNumberRepresentation(int num, bool hasConstant/*= false*/, bool hasRegister/*= false*/, bool isRamCall/*= false*/)
{
    if (hasConstant)
    {
        num |= 1 << constBitMove;
    }

    if (hasRegister)
    {
        num |= 1 << regBitMove;
    }

    if (isRamCall)
    {
        num |= 1 << ramBitMove;
    }

    return num;
}

int decodeNumberRepresentation(int codeNum/* = NULL*/, bool* hasConstant/* = NULL*/, bool* hasRegister/* = NULL*/, bool* isRamCall/* = NULL*/)
{
    int answer = codeNum;
    if (hasConstant) *hasConstant = (bool((1 << constBitMove) & codeNum));
    if (hasRegister) *hasRegister = (bool((1 << regBitMove)   & codeNum));
    if (isRamCall)   *isRamCall   = (bool((1 << ramBitMove)   & codeNum));
                               
    answer &= ~(1 << constBitMove);
    answer &= ~(1 << regBitMove);
    answer &= ~(1 << ramBitMove);

    return answer;
}