#pragma once

#include "CompileCommands.h"

#include <exception>

#include "ByteConverter.cpp"
#include "CompileData.cpp"
#include "CommonCode.cpp"

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    int writeNum = codeToNumberRepresentation(commandNum, 0, 0);
    compileData.put(writeNum);
    return WellCode;
}


int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data)
{
    if (!data.empty())
    {
        //int* number = new int{};
        //*number = _wtoi(data.data());

        bool isConstant = isDigitStr(data);

        int writeNum = codeToNumberRepresentation(commandNum, isConstant, 0);
        compileData.put(writeNum);

        //compileData.put(number);

        return WellCode;
    }

    throw std::exception("data.empty()");
    return CommandWriteDataCode;
}