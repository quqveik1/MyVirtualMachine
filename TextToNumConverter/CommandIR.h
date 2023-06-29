#pragma once

#include <string_view>
#include <vector>

#include "BufferObj.h"

struct CommandIR : BufferObj
{
    CommandIR();
private:
    std::wstring_view* line;

public:
    std::wstring_view* getLine() {return line;}
    void setLine(std::wstring_view* newLine) {line = newLine;}
};