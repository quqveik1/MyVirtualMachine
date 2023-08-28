#pragma once

#include "CommandIR.h"

#include "../Common/BufferObj.cpp"

CommandIR::CommandIR() :
    BufferObj(),
    line(nullptr)
{
    
}

std::wstring CommandIR::toString()
{
    wchar_t buffer[60]{};
    int res = swprintf_s(buffer, 60, L"commandNum: %04d; isFinal: %d; labelLinePos: %04d;", commandNum, getIsFinal(), getLabelLinePos());

    std::wstring ans = buffer;

    return ans;
}

char* CommandIR::getCommandData()
{
    return &getData()[sizeof(int)];
}