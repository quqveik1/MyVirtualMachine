#pragma once

#include "InteractiveMode.h"
#include "../Constants/ErrorCode.h"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode code)
{
    defaultPrint(processor);
    std::cout << "Запущен интерактивный режим\n";
    if (code != ErrorCode::WellCode)
    {
        std::cout << "Он был вызван из-за ошибки " << code << "\n";
    }

    return ErrorCode::WellCode;
}

ErrorCode defaultPrint(Processor& processor)
{
    printRuntimeInfoDissassembler(processor);
    printRuntimeData(processor);
    printCallStack(processor);
    printRegisters(processor);
    return ErrorCode::WellCode;
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

void printRegisters(Processor& processor)
{
    processor.getAppRegister().print();
}