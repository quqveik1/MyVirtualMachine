#pragma once

#include "InteractiveMode.h"

#include "../Constants/ErrorCode.h"
#include "../TextToNumConverter/Parser/ParseCommand.cpp"
#include "InteractiveModeConstants.cpp"
#include "InteractiveCommands.cpp"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode errorCode, InteractiveCode& code)
{
    defaultPrint(processor);
    std::cout << "Запущен интерактивный режим\n";
    if (errorCode != ErrorCode::WellCode || errorCode != ErrorCode::DebugBreakCode)
    {
        std::cout << "Он был вызван из-за ошибки " << errorCode << "\n";
    }

    std::wstring line{};

    for(;;)
    {
        std::getline(std::wcin, line);

        InteractiveCode code = Nothing;

        if (line.empty()) continue;

        ErrorCode res = executeCommand(processor, line, code);
        if(res != WellCode)
        {
            if (res == InteractiveCommandNotFound)
            {
                std::cout << "Не найдено такой комманды\n";
            }
            else
            {
                std::cout << "Ошибка выполнения комманды: " << res << std::endl;
            }
        }

        if (code == ShutDownProgramm) break;
    }

    if(errorCode == DebugBreakCode)
    {
        code = ContinueExecuting;
    }

    return ErrorCode::WellCode;
}

ErrorCode executeCommand(Processor& processor, std::wstring& line, InteractiveCode& code)
{
    std::wstring command{}, data{};

    splitCommand(line, command, data);

    INTERACTVECOMMAND fnc = getInteractiveCommand(command);

    if(!fnc)
    {
        return ErrorCode::InteractiveCommandNotFound;
    }

    ErrorCode res = fnc(processor, code, data);

    return res;
}

ErrorCode defaultPrint(Processor& processor)
{
    printRuntimeInfoDissassembler(processor);
    printRuntimeData(processor);
    printCallStack(processor);
    printRegisters(processor);
    return ErrorCode::WellCode;
}