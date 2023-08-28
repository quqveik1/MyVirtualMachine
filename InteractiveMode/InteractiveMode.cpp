#pragma once

#include "InteractiveMode.h"

#include "../Constants/ErrorCode.h"
#include "../TextToNumConverter/Parser/ParseCommand.cpp"
#include "InteractiveModeConstants.cpp"
#include "InteractiveCommands.cpp"
#include "InteractiveCode.h"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode errorCode, InteractiveCode& code)
{
    std::cout << "-----Interactive mode launched-----\n";

    processor.getBreakpoints().removeAllOnlyFromCode();

    defaultPrint(processor);

    if (errorCode != ErrorCode::WellCode && errorCode != ErrorCode::DebugBreakCode)
    {
        std::cout << "It was triggered due to error " << std::dec << (int)errorCode << "\n";
    }

    code = ContinueInteractiveMode;

    std::wstring line{};

    bool needToWriteArrow = true;

    for(;;)
    {
        if(needToWriteArrow)std::cout << "-> ";
        std::getline(std::wcin, line);
        needToWriteArrow = true;

        if (line.empty())
        {
            needToWriteArrow = false;
            continue;
        }

        std::wstring_view line_view = line;

        ErrorCode res = executeCommand(processor, line_view, code);
        if(res != ErrorCode::WellCode)
        {
            if (res == ErrorCode::InteractiveCommandNotFound)
            {
                std::cout << "Command not found\n";
            }
            else
            {
                std::cout << "Command execution error: " << std::dec << (int)res << std::endl;
            }
        }

        if (code != ContinueInteractiveMode) break;
        std::cout << "\n";
    }

    processor.getBreakpoints().insertAllBack();

    std::cout << "-----End of interactive mode-----\n";

    return ErrorCode::WellCode;
}

ErrorCode executeCommand(Processor& processor, std::wstring_view& line, InteractiveCode& code)
{
    std::wstring_view command{}, data{};

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
    std::cout << "\n";
    printRuntimeInfoDissassembler(processor);
    std::cout << "\n";
    printRuntimeData(processor);
    std::cout << "\n";
    printCallStack(processor);
    std::cout << "\n";
    printRegisters(processor);
    std::cout << "\n";
    return ErrorCode::WellCode;
}
