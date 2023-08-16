#pragma once

#include <string_view>
#include <vector>

#include "../Common/BufferObj.h"
#include "../../Constants/CommandConstants.h"

struct CommandIR : BufferObj
{
    CommandIR();
private:
    CommandType commandNum = 0;
    bool isFinal = true;
    int labelLinePos = -1;
    int linePos = -1;
    std::wstring_view* line;

public:
    std::wstring_view* getLine() {return line;}
    void setLine              (std::wstring_view* newLine) {line = newLine;}

    CommandType getCommandNum () const { return commandNum; }
    void        setCommandNum (CommandType newCommandNum) { commandNum = newCommandNum; }

    bool getIsFinal           () const { return isFinal; }
    void setIsFinal           (bool newIsFinal) { isFinal = newIsFinal; }

    bool getHasLabel          () const { return labelLinePos >= 0; }

    int  getLabelLinePos      () const { return labelLinePos; }
    void setLabelLinePos      (int _labelLinePos) { labelLinePos = _labelLinePos; }
    int  getLinePos           () const { return linePos; }
    void setLinePos           (int _linePos) { linePos = _linePos; }

    std::wstring toString     ();

    char* getCommandData      ();
};