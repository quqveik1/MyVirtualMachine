#pragma once

#include "BinCompileData.h"

#include "WordSearch.cpp"
#include "BufferObj.cpp"

BinCompileData::BinCompileData() :
    BufferObj(),
    wordSearch(this)
{
    
}