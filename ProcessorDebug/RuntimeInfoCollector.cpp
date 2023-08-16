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

void RuntimeInfoCollector::addLastCommand(int commandFileStart, int commandData)
{
    RuntimeCommandInfo command;

    command.commandData = commandData;
    command.commandStart = commandFileStart;
    command.commandFinish = processor.getCommandData().getCurrPos();

    pushCommand(command);
}

ErrorCode RuntimeInfoCollector::onError()
{ 
    initDisassemblerCommands();
    initRegisterNames();

    return print();
}

ErrorCode RuntimeInfoCollector::print()
{
    std::cout << "Последние " << HistoryLen << " полностью исполненных комманд:  \n";


    for (size_t i = 0; i < getCommands().size(); i++)
    {
        std::wstring ans{};

        RuntimeCommandInfo& info = getCommands().at(i);

        ErrorCode res = disassemble(ans, info);
        if (res != ErrorCode::WellCode) return res;

        std::cout << std::setw(3) << std::setfill('0') << std::right << std::dec << i << " | ";

        std::cout << std::setw(5) << std::setfill('0') << std::hex << std::right << info.commandStart;

        static const int marginData = 11;

        std::wstring output;
        char* arr = processor.getCommandData().getArr();

        printByteData(&arr, info.commandStart, info.commandFinish, ans, marginData, output, PrintByteDataLen);

        std::wcout << output;

        std::cout << std::endl;
    }

    std::cout << std::dec;

    return ErrorCode::WellCode;
}

ErrorCode RuntimeInfoCollector::disassemble(std::wstring& ans, RuntimeCommandInfo& info)
{
    int decodedCommandNum = decodeNumberRepresentation(info.commandData);
    DISASSEMBLERCOMMANDS fnc = disassemblerCommands[decodedCommandNum];

    int originalFileStartPos = processor.getCommandData().getCurrPos();

    if (fnc == nullptr)
    {
        fnc = defaultOnlyName_dissassemblerCommand;
    }

    ErrorCode res = fnc(processor, info, ans);

    processor.getCommandData().setCurrPos(originalFileStartPos);

    return res;
}