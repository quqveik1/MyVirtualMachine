#pragma once

#include "CommandIR.h"

#include "BufferObj.cpp"

CommandIR::CommandIR() :
    BufferObj(),
    line(nullptr)
{
    
}

std::wstring CommandIR::toString()
{
    wchar_t buffer[50]{};
    swprintf_s(buffer, 50, L"commandNum: %04d, isFinal: %d", commandNum, isFinal);

    std::wstring ans = buffer;

    return ans;
}