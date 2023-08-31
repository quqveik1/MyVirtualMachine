#pragma once

#include "Compile1Commands.h"

#include <exception>
#include <iostream>
#include <map>

#include "../../Converter/ByteConverter.cpp"
#include "IR/CommandIR.cpp"
#include "../../Common/CommonCode.cpp"
#include "../../Processor/Register/RegisterCompile.cpp"
#include "../../Constants/CommandConstants.h"
#include "../../Converter/FloatConvert.cpp"
#include "../../Common/StringViewExtension.cpp"
#include "../IR/CommandIR.cpp"
#include "../../Constants/SystemInfo.cpp"

ErrorCode default_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    int writeNum = codeToNumberRepresentation(commandNum);
    commandIR.put(writeNum);
    return ErrorCode::WellCode;
}

ErrorCode out_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    if(data.empty())
    {
        return default_1compile(commandIR, commandNum, data, ir);
    }

    if (isJmpWord(data))
    {
        return saveWordExpression(commandIR, commandNum, data, ir);
    }

    return saveSmallExpr(commandIR, commandNum, data, 16);
}

//data type: const+arg
ErrorCode push_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    return saveSmallExpr(commandIR, commandNum, data);
}

ErrorCode saveSmallExpr(CommandIR& commandIR, int commandNum, std::wstring_view& data, int base/* = 10*/)
{
    if (!data.empty())
    {
        std::wstring_view    firstArg{}, secondArg{};
        CommandDataFloatType first{}, second{};
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

            ErrorCode res = convertArg(second, secondArg, &isConstant, &isReg, base);

            if(res != ErrorCode::WellCode)
            {
                return res;
            }

            needToSwapArgs = isConstant;
        }

        ErrorCode res = convertArg(first, firstArg, &isConstant, &isReg, base);

        if (res != ErrorCode::WellCode)
        {
            return res;
        }

        CommandType writeNum = codeToNumberRepresentation(commandNum, isConstant, isReg, isRamCall);
        commandIR.put(writeNum);

        if (needToSwapArgs)
        {
            std::swap(first, second);
        }

        CommandDataType _f = convNum(first);
        commandIR.put(_f);

        if (plusPos >= 0)
        {
            CommandDataType _s = convNum(second);
            commandIR.put(_s);
        }

        return ErrorCode::WellCode;
    }

    throw std::exception("data.empty()");
    return ErrorCode::CommandWriteDataCode;
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

bool isJmpWord(std::wstring_view& arg)
{
    bool isReg = isRegister(arg);

    if (isReg) return false;

    if (!iswalpha(arg[0]) && arg[0] != L'_')
    {
        return false;
    }

    for (wchar_t c : arg)
    {
        if (!iswalnum(c) && c != L'_')
        {
            return false;
        }
    }

    return true;
}

ErrorCode convertArg(double& ans, std::wstring_view& arg, bool* isNumber, bool* reg, int base/* = 10*/)
{
    if (!isRegister(arg))
    {
        *isNumber = true;
        try
        {
            if (base != 10)
            {
                ans = strToNum(arg, base);
            }
            else
            {
                ans = strToFloat<double>(arg);
            }
        }
        catch (std::exception e)
        {
            std::cout << e.what() << "\n";
            return ErrorCode::SymbolConvertationError;
        }
        return ErrorCode::WellCode;
    }
    else
    {
        *reg = true;
        int registerNum = 0;
        ErrorCode res = getRegisterNumFromStr(arg, registerNum);

        if(res == ErrorCode::WellCode)
        {
            ans = registerNum;
        }

        return res;
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

ErrorCode pop_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    return saveSmallExpr(commandIR, commandNum, data);
}

ErrorCode jmp_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    if(isJmpWord(data))
    {
        return saveWordExpression(commandIR, commandNum, data, ir);
    }

    return saveSmallExpr(commandIR, commandNum, data, 16);
}

ErrorCode saveWordExpression(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    int codedCommandNum = codeToNumberRepresentation(commandNum, true);
    commandIR.put(codedCommandNum);

    ir.getLabelSearchIR().writeOrWaitLabel(data, &commandIR);
    return ErrorCode::WellCode;
}

const std::map<wchar_t, wchar_t> specialChars = {
                                                {L'n', L'\n'},
                                                {L'r', L'\r'},
                                                {L't', L'\t'},
                                                {L'\\', L'\\'}};

ErrorCode db_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    size_t firstQuotePos = data.find(L'"');

    if(firstQuotePos == std::wstring_view::npos)
    {
        return ErrorCode::NoQuoteDBError;
    }

    size_t secondQuotePos = data.rfind(L'"');

    if(firstQuotePos == secondQuotePos)
    {
        return ErrorCode::NoQuoteDBError;
    }

    return writeStrInData(commandIR, data, firstQuotePos, secondQuotePos);
}

ErrorCode writeStrInData(CommandIR& commandIR, std::wstring_view& data, size_t firstQuotePos, size_t secondQuotePos)
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
                    commandIR.put(it->second);
                    i++;
                    continue;
                }
                else
                {
                    throw std::exception("unknown symbol after \\");
                    return ErrorCode::CommandDataReadError;
                }
            }
        }

        commandIR.put(data[i]);
    }

    const wchar_t nullSymbol = 0;
    commandIR.put(nullSymbol);

    return ErrorCode::WellCode;
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


ErrorCode word_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    //default_1compile(commandIR, commandNum, data, ir);

    commandIR.setLabelLinePos((int)ir.getActiveCommandNum());

    ir.getLabelSearchIR().pushWord(data);

    return ErrorCode::WellCode;
}

ErrorCode rdsys_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir)
{
    int code = getComponentNumFromStr(data);

    if(code == error)
    {
        return ErrorCode::SystemComponentNotFounded;
    }

    default_1compile(commandIR, commandNum, data, ir);

    commandIR.put(code);

    return ErrorCode::WellCode;
}