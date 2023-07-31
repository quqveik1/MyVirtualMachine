#pragma once

#include "RegisterCompile.h"

#include "../../Constants/CommandConstants.h" 

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

    return RegisterNotFound;
}


std::vector<std::wstring> registerNames;

int getRegisterStrFromNum(int num, std::wstring& reg)
{
    bool res = isRegisterValid(num);

    if(!res) return RegisterNotFound;

    reg = registerNames[num];

    return WellCode;
}

void initRegisterNames()
{
    registerNames =
    {
        ax_string,
        bx_string,
        cx_string,
        dx_string
    };
}

bool isRegisterValid(int num)
{
    if (0 <= num && num < cRegister)
    {
        return true;
    }

    return false;
}