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
    wchar_t buffer[7]{};
    //swprintf_s(buffer, 7, L"")
}