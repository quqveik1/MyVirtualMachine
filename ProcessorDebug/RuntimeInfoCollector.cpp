#pragma once

#include "RuntimeInfoCollector.h"

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

void RuntimeInfoCollector::print()
{
    std::cout << "\nПоследние " << HistoryLen << " полностью исполненных комманд:  \n";

    std::cout << "   | CommandNum | File pos\n";

    if (!getCommands().empty())
    {
        
        for (int i = 0; !getCommands().empty(); i++)
        {
            std::cout << std::setw(2) << std::setfill('0') << std::right << i << " | ";

            std::cout << std::setw(3) << std::setfill('0') << std::right << std::hex << getCommands().front().commandNum << std::setfill(' ') << std::setw(10) << " | ";

            std::cout << std::setw(5) << std::setfill('0') << std::right << getCommands().front().commandStart;

            std::cout << std::endl;

            getCommands().pop();
        }
    }

    std::cout << std::dec;


}