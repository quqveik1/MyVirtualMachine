#pragma once

#include "RegisterCompile.h"

#include "../../Constants/CommandConstants.h" 

ErrorCode getRegisterNumFromStr(std::wstring_view& str, int& regNum)
{
    if (str == ax_string)
    {
        regNum =  ax_numeric;

        return ErrorCode::WellCode;
    }
    if (str == bx_string)
    {
        regNum = bx_numeric;

        return ErrorCode::WellCode;
    }
    if (str == cx_string)
    {
        regNum = cx_numeric;

        return ErrorCode::WellCode;
    }
    if (str == dx_string)
    {
        regNum = dx_numeric;

        return ErrorCode::WellCode;
    }

    //throw std::exception("Не найден регистр");

    return ErrorCode::RegisterNotFound;
}


std::vector<std::wstring> registerNames;

ErrorCode getRegisterStrFromNum(int num, std::wstring& reg)
{
    bool res = isRegisterValid(num);

    if(!res) return  ErrorCode::RegisterNotFound;

    reg = registerNames[num];

    return  ErrorCode::WellCode;
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

bool isRegister(std::wstring_view& arg)
{
    int regNum = 0;
    ErrorCode num = getRegisterNumFromStr(arg, regNum);

    return num == ErrorCode::WellCode;
}