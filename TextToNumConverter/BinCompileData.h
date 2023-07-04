#pragma once

#include <vector>

#include "LabelSearchBin.h"
#include "BufferObj.h"

struct BinCompileData : BufferObj
{
    BinCompileData();

private:
    LabelSearchBin labelSearchBin;
    std::vector<size_t> bufferLineStart;
    std::vector<size_t> bufferLineFinish;
    size_t activeLineNum = 0;

public:
    LabelSearchBin& getLabelSearchBin() { return labelSearchBin; };
    void addNewLineStart(size_t pos) { bufferLineStart.push_back(pos); };
    void addNewLineFinish(size_t pos) { bufferLineFinish.push_back(pos); };
    std::vector<size_t>& getBufferLineStart() { return bufferLineStart; };
    std::vector<size_t>& getBufferLineFinish() { return bufferLineFinish; };

    size_t getActiveLineNum() { return activeLineNum; };
    void setActiveLineNum(size_t i) {  activeLineNum = i; };
};