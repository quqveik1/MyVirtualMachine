#pragma once

#include "BinCompileData.h"

#include "LabelSearchBin.cpp"
#include "BufferObj.cpp"

BinCompileData::BinCompileData() :
    BufferObj(),
    labelSearchBin(this)
{
    
}