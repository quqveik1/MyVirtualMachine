#pragma once

#include "DisassemblerCommands.h"

#include "..\..\CommandConstants.h"
#include "..\..\RegisterCompile.cpp"
#include "..\..\StringViewExtension.cpp"

int defaultOnlyName_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return getCommandName(commandInfo.commandNum, originalLine);
}

int defaultSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return defaultSmallExpression(processor, commandInfo, originalLine);
}

int defaultSmallExpression(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine, int constantBase/* = 10*/, int* finishPos/* = nullptr*/)
{
    int res = defaultOnlyName_dissassemblerCommand(processor, commandInfo, originalLine);
    if (res != WellCode) return res;

    int startFilePos = processor.getCommandData().getCurrPos();

    processor.getCommandData().setCurrPos(commandInfo.commandStart);

    int codedNum = *processor.getCommandData().peek<int>();

    bool hasConstant = false;
    bool hasRegister = false;
    bool hasRam = false;

    decodeNumberRepresentation(codedNum, &hasConstant, &hasRegister, &hasRam);

    originalLine += L" ";

    if (hasRam)
    {
        originalLine += L"[";
    }

    if (hasConstant)
    {
        int constNum = *processor.getCommandData().peek<int>();

        constNum = deConvNum<int>(constNum);

        std::wstringstream ss;
        ss << std::setbase(constantBase) << constNum;

        std::wstring result = ss.str();
        originalLine += result;
    }

    if (hasConstant && hasRegister)
    {
        originalLine += L" + ";
    }

    if (hasRegister)
    {
        int regNum = *processor.getCommandData().peek<int>();

        regNum = deConvNum<int>(regNum);

        std::wstring regName;

        int res = getRegisterStrFromNum(regNum, regName);

        if (res != WellCode) return res;

        originalLine += regName;
    }

    if (hasRam)
    {
        originalLine += L"]";
    }

    if(finishPos)
    {
        *finishPos = processor.getCommandData().getCurrPos();
    }

    processor.getCommandData().setCurrPos(startFilePos);

    return WellCode;
}


int hexSaveSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return defaultSmallExpression(processor, commandInfo, originalLine, 16);
}

int jmp_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    int finishPos = 0;
    int res = defaultSmallExpression(processor, commandInfo, originalLine, 16, &finishPos);

    if (res != WellCode) return res;

    commandInfo.commandFinish = finishPos;

    return WellCode;
}