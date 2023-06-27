#pragma once

#include "RegisterCompile.h"

int getRegisterNumFromStr(std::wstring_view& str)
{
    if (str == ax_string)
    {
        return ax_numeric;
    }
    if (str == bx_string)
    {
        return bx_numeric;
    }
    if (str == cx_string)
    {
        return cx_numeric;
    }
    if (str == dx_string)
    {
        return dx_numeric;
    }

    //throw std::exception("Не найден регистр");

    return -1;
}