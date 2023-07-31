#pragma once

#include <string>

#include "CommonCode.h"


bool checkArrBound(int arrSize, int elNum)
{
    if (0 <= elNum && elNum < arrSize)
    {
        return true;
    }
    return false;
}

template<typename T>
bool isDigitStr(T& str)
{
    for (wchar_t c : str)
    {
        if (!iswdigit(c) && c != L'-')
        {
            return false;
        }
    }

    return true;
}