#pragma once

#include "Register.h"

#include <exception>

#include "../../Common/CommonCode.h"
#include "RegisterCompile.cpp"
#include "../../Converter/FloatConvert.h"

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

void Register::print(bool needToConvertToUserRepresentation/* = true*/)
{
    std::cout << "Распечатка регистров: \n";

    std::wstring regName{};

    for (int i = 0; i < cRegister; i++)
    {
        int data = getReg(i);

        getRegisterStrFromNum(i, regName);

        std::wcout << regName << ": ";

        if(needToConvertToUserRepresentation)
        {
            float userForm = deConvNum<float>(data);
            std::cout << userForm;
        }
        else
        {
            std::cout << data;
        }

        std::cout << "\n";
         
    }

    std::cout << "Конец распечатки регистров\n\n";
}