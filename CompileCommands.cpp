#pragma once

#include "CompileCommands.h"

#include <exception>

#include "ByteConverter.cpp"
#include "CompileData.cpp"
#include "CommonCode.cpp"
#include "RegisterCompile.cpp"
#include "CommandConstants.h"

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    int writeNum = codeToNumberRepresentation(commandNum, 0, 0);
    compileData.put(writeNum);
    return WellCode;
}

int convertArgToInt(std::wstring_view& arg, bool* constant, bool* reg)
{
    if(isDigitStr(arg))
    {
        *constant = true;
        int number = std::stoi((std::wstring)arg);
        return number;
    }
    else
    {
        *reg = true;
        int number = getRegisterNumFromStr(arg);
        return number;
    }

}
//data type: const+arg
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    if (!data.empty())
    {
        int plusPos = (int)data.find(L'+');
        std::wstring_view firstArg{}, secondArg{};
        int               firstInt{}, secondInt{};
        bool needToSwapArgs = false;

        firstArg = data;

        bool isConstant = false;
        bool isReg = false;

        if(plusPos >= 0)
        {
            firstArg = data.substr(0, plusPos);
            secondArg = data.substr(plusPos + 1);

            secondInt = convertArgToInt(secondArg, &isConstant, &isReg);

            needToSwapArgs = isReg;
        }

        firstInt = convertArgToInt(firstArg, &isConstant, &isReg);

        int writeNum = codeToNumberRepresentation(commandNum, isConstant, isReg);
        compileData.put(writeNum);

        if(needToSwapArgs)
        {
            std::swap(firstInt, secondInt);
        }

        compileData.put(firstInt);

        if (plusPos >= 0)
        {
            compileData.put(secondInt);
        }

        return WellCode;
    }

    throw std::exception("data.empty()");
    return CommandWriteDataCode;
}