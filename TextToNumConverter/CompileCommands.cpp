#pragma once

#include "CompileCommands.h"

#include <exception>
#include <iostream>
#include <map>

#include "../ByteConverter.cpp"
#include "CompileData.cpp"
#include "../CommonCode.cpp"
#include "../RegisterCompile.cpp"
#include "../CommandConstants.h"
#include "../FloatConvert.cpp"
#include "../StringViewExtension.cpp"

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    int writeNum = codeToNumberRepresentation(commandNum);
    compileData.put(writeNum);
    return WellCode;
}

int out_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    if(data.empty())
    {
        return default_compile(compileData, commandNum, data);
    }

    return saveSmallExpr(compileData, commandNum, data, 16);
}

//data type: const+arg
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    return saveSmallExpr(compileData, commandNum, data);
}

int saveSmallExpr(CompileData& compileData, int commandNum, std::wstring_view& data, int base/* = 10*/)
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

            second = convertArg(secondArg, &isConstant, &isReg, base);

            needToSwapArgs = isConstant;
        }

        first = convertArg(firstArg, &isConstant, &isReg, base);

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

bool isRegister(std::wstring_view& arg)
{
    size_t xpos = arg.find(L'x');

    if(xpos != std::wstring_view::npos)
    {
        return true;
    }

    return false;
}

double convertArg(std::wstring_view& arg, bool* isNumber, bool* reg, int base/* = 10*/)
{
    if (!isRegister(arg))
    {
        *isNumber = true;
        double number = 0;
        if(base != 10)
        {
            number = strToNum(arg, base);
        }
        else
        {
            number = strToFloat<double>(arg);
        }
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
    return saveSmallExpr(compileData, commandNum, data, 16);
}

const std::map<wchar_t, wchar_t> specialChars = {
                                                {L'n', L'\n'},
                                                {L'r', L'\r'},
                                                {L't', L'\t'},
                                                {L'\\', L'\\'}};

int db_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    size_t firstQuotePos = data.find(L'"');

    if(firstQuotePos == std::wstring_view::npos)
    {
        return NoQuoteDBError;
    }

    size_t secondQuotePos = data.rfind(L'"');

    if(firstQuotePos == secondQuotePos)
    {
        return NoQuoteDBError;
    }

    return writeStrInData(compileData, data, firstQuotePos, secondQuotePos);
}

int writeStrInData(CompileData& compileData, std::wstring_view& data, size_t firstQuotePos, size_t secondQuotePos)
{
    for (size_t i = firstQuotePos + 1; i < secondQuotePos; i++)
    {
        if (data[i] == L'\\')
        {
            if (i + 1 < secondQuotePos)
            {
                auto it = specialChars.find(data[i + 1]);

                if (it != specialChars.end())
                {
                    compileData.put(it->second);
                    i++;
                    continue;
                }
                else
                {
                    throw std::exception("unknown symbol after \\");
                    return CommandDataReadError;
                }
            }
        }

        compileData.put(data[i]);
    }

    const wchar_t nullSymbol = 0;
    compileData.put(nullSymbol);

    return WellCode;
}

size_t cDeletedSymAfterCompilation(const std::wstring_view& str)
{
    size_t ans = 0;
    for(size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == L'\\')
        {
            i++;
            ans++;
        }
    }

    return ans;
}