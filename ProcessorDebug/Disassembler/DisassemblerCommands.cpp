#pragma once

#include "DisassemblerCommands.h"

#include "../../Constants/CommandConstants.h"
#include "../../Processor/Register/RegisterCompile.cpp"
#include "../../Common//StringViewExtension.cpp"
#include "../../Constants/SystemInfo.cpp"

ErrorCode defaultOnlyName_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    int decodedNum = decodeNumberRepresentation(commandInfo.commandData);
    return getCommandName(decodedNum, originalLine);
}

ErrorCode defaultSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return defaultSmallExpression(processor, commandInfo, originalLine);
}

ErrorCode defaultSmallExpression(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine, int constantBase/* = 10*/, int* finishPos/* = nullptr*/)
{
    ErrorCode res = defaultOnlyName_dissassemblerCommand(processor, commandInfo, originalLine);
    if (res != ErrorCode::WellCode) return res;

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

        ErrorCode res = getRegisterStrFromNum(regNum, regName);

        if (res != ErrorCode::WellCode) return res;

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

    return ErrorCode::WellCode;
}


ErrorCode hexSaveSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return defaultSmallExpression(processor, commandInfo, originalLine, 16);
}

ErrorCode jmp_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    int finishPos = 0;
    ErrorCode res = defaultSmallExpression(processor, commandInfo, originalLine, 16, &finishPos);

    if (res != ErrorCode::WellCode) return res;

    commandInfo.commandFinish = finishPos;

    return  ErrorCode::WellCode;
}

ErrorCode ret_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    commandInfo.commandFinish = commandInfo.commandStart + sizeof(int);

    return defaultOnlyName_dissassemblerCommand(processor, commandInfo, originalLine);
}

ErrorCode rdsys_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    defaultOnlyName_dissassemblerCommand(processor, commandInfo, originalLine);

    processor.getCommandData().setCurrPos(commandInfo.commandStart + sizeof(int));

    int compNum = *processor.getCommandData().peek<int>();

    std::wstring compName{};

    ErrorCode res = getComponentStrFromNum((SystemComponents)compNum, compName);

    if (res != ErrorCode::WellCode) return res;

    originalLine += L" ";

    originalLine += compName;

    return ErrorCode::WellCode;
}