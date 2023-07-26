#pragma once

#include "RuntimeInfoCollector.h"

#include "Disassembler/DisassemblerCommands.cpp"
#include "Disassembler/DisassemblerArrs.cpp"
#include "..\CommandConstants.h"

RuntimeInfoCollector::RuntimeInfoCollector(Processor& _processor) :
    processor(_processor)
{
}

void RuntimeInfoCollector::pushCommand(RuntimeCommandInfo& info)
{
    if (getCommands().size() >= HistoryLen)
    {
        getCommands().pop();
    }
    getCommands().push(info);
}

void RuntimeInfoCollector::addLastCommand(int commandFileStart, int commandNum)
{
    RuntimeCommandInfo command;

    command.commandNum = commandNum;
    command.commandStart = commandFileStart;
    command.commandFinish = processor.getCommandData().getCurrPos();

    pushCommand(command);
}

int RuntimeInfoCollector::print()
{
    initCommandsNameArr();
    initDisassemblerCommands();

    std::cout << "\nПоследние " << HistoryLen << " полностью исполненных комманд:  \n";

    std::cout << "   | Command num | File pos | Disassembled code\n";

    if (!getCommands().empty())
    {
        for (int i = 0; !getCommands().empty(); i++)
        {
            std::wstring ans;

            int res = disassemble(ans, getCommands().front());

            if (res != WellCode) return res;

            std::cout << std::setw(2) << std::setfill('0') << std::right << std::dec << i << " | ";

            std::cout << std::setw(3) << std::setfill('0') << std::right << std::hex << getCommands().front().commandNum << std::setfill(' ') << std::setw(11) << " | ";

            std::cout << std::setw(5) << std::setfill('0') << std::right << getCommands().front().commandStart << std::setfill(' ') << std::setw(6) << " | ";

            std::wcout << ans;

            std::cout << std::endl;

            getCommands().pop();
        }
    }

    std::cout << std::dec;

    return WellCode;
}

int RuntimeInfoCollector::disassemble(std::wstring& ans, RuntimeCommandInfo& info)
{
    DISASSEMBLERCOMMANDS fnc = disassemblerCommands[info.commandNum];

    if (fnc == nullptr)
    {
        fnc = defaultOnlyName_dissassemblerCommand;
    }

    int res = fnc(processor, info, ans);

    return res;
}