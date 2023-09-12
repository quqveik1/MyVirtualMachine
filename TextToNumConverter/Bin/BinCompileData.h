#pragma once

#include <vector>

#include "LabelSearchBin.h"
#include "../Common/BufferObj.h"

struct BinCompileData : BufferObj
{
    BinCompileData();

private:
    LabelSearchBin      labelSearchBin;

public:
    LabelSearchBin& getLabelSearchBin       () { return labelSearchBin; };

    ErrorCode finishWork                    ();
};