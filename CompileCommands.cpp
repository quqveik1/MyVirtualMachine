#pragma once

#include "CompileCommands.h"

#include <exception>
#include <iostream>

#include "ByteConverter.cpp"
#include "CompileData.cpp"
#include "CommonCode.cpp"
#include "RegisterCompile.cpp"
#include "CommandConstants.h"

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
        int               firstInt{}, secondInt{};
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

            secondInt = convertArgToInt(secondArg, &isConstant, &isReg);

            needToSwapArgs = isConstant;
        }

        firstInt = convertArgToInt(firstArg, &isConstant, &isReg);

        int writeNum = codeToNumberRepresentation(commandNum, isConstant, isReg, isRamCall);
        compileData.put(writeNum);

        if (needToSwapArgs)
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

int convertArgToInt(std::wstring_view& arg, bool* number, bool* reg)
{
    if (isDigitStr(arg))
    {
        *number = true;
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