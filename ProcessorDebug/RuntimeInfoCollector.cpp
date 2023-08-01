#pragma once

#include "RuntimeInfoCollector.h"

#include "Disassembler/DisassemblerCommands.cpp"
#include "Disassembler/DisassemblerArrs.cpp"
#include "../Constants/CommandConstants.h"
#include "../Processor/Register/RegisterCompile.h"
#include "../StrFormatting/PrintByteData.cpp"

RuntimeInfoCollector::RuntimeInfoCollector(Processor& _processor) :
    processor(_processor)
{
}

void RuntimeInfoCollector::pushCommand(RuntimeCommandInfo& info)
{
    if (getCommands().size() >= HistoryLen)
    {
        getCommands().pop_front();
    }
    getCommands().push_back(info);
}

void RuntimeInfoCollector::addLastCommand(int commandFileStart, int commandNum)
{
    RuntimeCommandInfo command;

    command.commandNum = commandNum;
    command.commandStart = commandFileStart;
    command.commandFinish = processor.getCommandData().getCurrPos();

    pushCommand(command);
}

int RuntimeInfoCollector::onError()
{ 
    initCommandsNameArr();
    initDisassemblerCommands();
    initRegisterNames();

    return print();
}

int RuntimeInfoCollector::print()
{
    std::cout << "\nПоследние " << HistoryLen << " полностью исполненных комманд:  \n";


    for (size_t i = 0; i < getCommands().size(); i++)
    {
        std::wstring ans;

        RuntimeCommandInfo& info = getCommands().at(i);

        int res = disassemble(ans, info);

        if (res != WellCode) return res;

        //static const int startLen = 

        std::cout << std::setw(2) << std::setfill('0') << std::right << std::dec << i << " | ";

        std::cout << std::setw(5) << std::setfill('0') << std::hex << std::right << info.commandStart;

        static const int marginData = 10;

        std::wstring output;
        char* arr = processor.getCommandData().getArr();

        printByteData(&arr, info.commandStart, info.commandFinish, ans, marginData, output, PrintByteDataLen);

        std::wcout << output;

        std::cout << std::endl;
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