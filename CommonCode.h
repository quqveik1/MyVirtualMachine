#pragma once


bool checkArrBound(int arrSize, int elNum)
{
    if (0 <= elNum && elNum < arrSize)
    {
        return true;
    }
    return false;
}