#pragma once

#include <exception>

#include "Register.h"
#include "CommonCode.h"

int Register::getReg(int num)
{
    if (checkArrBound(cRegister, num))
    {
        return arr[num];
    }
    else
    {
        throw std::exception("Выход за пределы массива");
        return 0;
    }
}

void Register::setReg(int num, int value)
{
    if (checkArrBound(cRegister, num))
    {
        arr[num] = value;
    }
    else
    {
        throw std::exception("Выход за пределы массива");
    }
}