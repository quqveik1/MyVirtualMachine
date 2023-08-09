#pragma once

#include <string_view>
#include <vector>

#include "../Common/BufferObj.h"

struct CommandIR : BufferObj
{
    CommandIR();
private:
    int commandNum = 0;
    bool isFinal = true;
    int labelLinePos = -1;
    std::wstring_view* line;

public:
    std::wstring_view* getLine() {return line;}
    void setLine              (std::wstring_view* newLine) {line = newLine;}

    int getCommandNum         () const { return commandNum; }
    void setCommandNum        (int newCommandNum) { commandNum = newCommandNum; }

    bool getIsFinal           () const { return isFinal; }
    void setIsFinal           (bool newIsFinal) { isFinal = newIsFinal; }

    bool getHasLabel          () const { return labelLinePos >= 0; }

    int getLabelLinePos       () const { return labelLinePos; }
    void setLabelLinePos      (int _labelLinePos) { labelLinePos = _labelLinePos; }

    std::wstring toString     ();

    char* getCommandData      ();
};