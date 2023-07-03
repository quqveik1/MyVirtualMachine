#pragma once

#include <vector>

#include "WordSearch.h"
#include "BufferObj.h"

struct BinCompileData : BufferObj
{
    BinCompileData();

private:
    WordSearch wordSearch;
    std::vector<size_t> bufferLineStart;
    std::vector<size_t> bufferLineFinish;

public:

    WordSearch& getWordSearch() { return wordSearch; };
   void addNewLineStart(size_t pos) { bufferLineStart.push_back(pos); };
   void addNewLineFinish(size_t pos) { bufferLineFinish.push_back(pos); };
   std::vector<size_t>& getBufferLineStart() { return bufferLineStart; };
   std::vector<size_t>& getBufferLineFinish() { return bufferLineFinish; };
};