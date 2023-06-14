#pragma once

#include "CompileCommands.h"

#include <exception>
#include <iostream>

#include "../ByteConverter.cpp"
#include "CompileData.cpp"
#include "../CommonCode.cpp"
#include "../RegisterCompile.cpp"
#include "../CommandConstants.h"
#include "../FloatConvert.cpp"

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    int writeNum = codeToNumberRepresentation(commandNum);
    compileData.put(writeNum);
    return WellCode;
}

//data type: const+arg
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    return saveSmallExpr(compileData, commandNum, data);
}

int saveSmallExpr(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    if (!data.empty())
    {
        std::wstring_view firstArg{}, secondArg{};
        double               first{}, second{};
        bool needToSwapArgs = false;

        bool isConstant = false;
        bool isReg = false;
        bool isRamCall = editDataForBrackets(data);

        int plusPos = (int)data.find(L'+');
        firstArg = data;

        if (plusPos >= 0)
        {
            firstArg = data.substr(0, plusPos);
            secondArg = data.substr(plusPos + 1);

            second = convertArg(secondArg, &isConstant, &isReg);

            needToSwapArgs = isConstant;
        }

        first = convertArg(firstArg, &isConstant, &isReg);

        int writeNum = codeToNumberRepresentation(commandNum, isConstant, isReg, isRamCall);
        compileData.put(writeNum);

        if (needToSwapArgs)
        {
            std::swap(first, second);
        }

        int _f = convNum(first);
        compileData.put(_f);

        if (plusPos >= 0)
        {
            int _s = convNum(second);
            compileData.put(_s);
        }

        return WellCode;
    }

    throw std::exception("data.empty()");
    return CommandWriteDataCode;
}

bool editDataForBrackets(std::wstring_view& data)
{
    int startPos = -1;
    int endPos = -1;

    findBrackets(data, startPos, endPos);

    if (startPos >= 0)
    {
        data = data.substr(startPos + 1, endPos - (startPos + 1));
        return true;
    }

    return false;
}

double convertArg(std::wstring_view& arg, bool* number, bool* reg)
{
    if (isDigitStr(arg))
    {
        *number = true;
        double number = std::stod((std::wstring)arg);
        return number;
    }
    else
    {
        *reg = true;
        double number = getRegisterNumFromStr(arg);
        return number;
    }
}

void findBrackets(std::wstring_view& data, int& startPos, int& endPos)
{
    int _startPos = (int)data.find(L'[');
    if (_startPos >= 0)
    {
        int _endPos = (int)data.find(L']');
        if (_endPos >= 0)
        {
            startPos = _startPos;
            endPos = _endPos;
            return;
        }
    }

    startPos = -1;
    endPos = -1;
}

int pop_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    return saveSmallExpr(compileData, commandNum, data);
}

int jmp_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    return saveSmallExpr(compileData, commandNum, data);
}