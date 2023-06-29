#pragma once

#include <string_view>

struct CommandIR
{
    char* buffer = NULL;
    int bufferLen = 0;
    std::wstring_view& line;
};