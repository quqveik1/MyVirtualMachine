#pragma once

#include "SystemInfo.h"

template <typename S>
SystemComponents getComponentNumFromStr(S& str)
{
    if (str == vsizex_str)
    {
        return vsizex_num;
    }
    else if (str == vsizey_str)
    {
        return vsizey_num;
    }

    return error;
}


ErrorCode getComponentStrFromNum(SystemComponents num, std::wstring& str)
{
    switch (num)
    {
    case vsizex_num:
        str= vsizex_str;
        return ErrorCode::WellCode;

    case vsizey_num:
        str = vsizex_str;
        return ErrorCode::WellCode;
    default:
        return ErrorCode::SystemComponentNotFounded;
    }
}