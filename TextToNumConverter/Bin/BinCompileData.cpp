#pragma once

#include "BinCompileData.h"

#include "LabelSearchBin.cpp"
#include "../Common/BufferObj.cpp"

BinCompileData::BinCompileData() :
    BufferObj(),
    labelSearchBin(this)
{
    
}

ErrorCode BinCompileData::finishWork()
{
    return labelSearchBin.checkLabelLinking();
}