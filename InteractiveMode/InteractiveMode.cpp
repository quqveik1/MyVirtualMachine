#pragma once

#include "InteractiveMode.h"

#include "../Constants/ErrorCode.h"
#include "../TextToNumConverter/Parser/ParseCommand.cpp"
#include "InteractiveModeConstants.cpp"
#include "InteractiveCommands.cpp"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode errorCode, InteractiveCode& code)
{
    std::cout << "-----Запущен интерактивный режим-----\n";
    defaultPrint(processor);
    
    if (errorCode != ErrorCode::WellCode && errorCode != ErrorCode::DebugBreakCode)
    {
        std::cout << "Он был вызван из-за ошибки " << std::dec << errorCode << "\n";
    }

    std::wstring line{};

    for(;;)
    {
        std::getline(std::wcin, line);

        code = ContinueInteractiveMode;

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
                std::cout << "Ошибка выполнения комманды: " << std::dec << res << std::endl;
            }
        }

        if (code != ContinueInteractiveMode) break;
    }

    std::cout << "-----Конец интерактивного режима-----\n";

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
