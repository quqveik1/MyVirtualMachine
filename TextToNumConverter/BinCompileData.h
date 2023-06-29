#pragma once

#include <vector>

#include "WordSearch.h"
#include "BufferObj.h"

struct BinCompileData : BufferObj
{
    BinCompileData();

private:
    WordSearch wordSearch;

public:

    WordSearch& getWordSearch() { return wordSearch; };
};