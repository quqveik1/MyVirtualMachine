#pragma once

#include "InteractiveCommands.h"

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    code = InteractiveCode::ShutDownProgramm;
    return WellCode;
}

ErrorCode info_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    if(data == L"r" || data == L"registers")
    {
        printRegisters(processor);
        return WellCode;
    }
    else if (data == L"s" || data == L"stack")
    {
        printRuntimeData(processor);
        return WellCode;
    }

    return CommandDataReadError;
}

ErrorCode backtrace_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    printCallStack(processor);
    return WellCode;
}

ErrorCode disassemble_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    printRuntimeInfoDissassembler(processor);
    return WellCode;
}

void printRegisters(Processor& processor)
{
    processor.getAppRegister().print();
}

void printRuntimeData(Processor& processor)
{
    int res = processor.getRuntimeData().print();
    if (res != WellCode)
    {
        std::cout << "Ошибка при выполении распечатки стека: " << res << std::endl;
    }
}

void printRuntimeInfoDissassembler(Processor& processor)
{
    int res = processor.getRuntimeInfoCollector().onError();
    if (res != WellCode)
    {
        std::cout << "Ошибка при выполении распечатки последних комманд: " << res << std::endl;
    }
}

void printCallStack(Processor& processor)
{
    processor.getCallStack().print();
}