#pragma once

#include <string_view>
#include <vector>

#include "BufferObj.h"

struct CommandIR : BufferObj
{
    CommandIR();
private:
    int commandNum = 0;
    std::wstring_view* line;

public:
    std::wstring_view* getLine() {return line;}
    void setLine(std::wstring_view* newLine) {line = newLine;}

    int getCommandNum() const { return commandNum; }
    void setCommandNum(int newCommandNum) { commandNum = newCommandNum; }
};