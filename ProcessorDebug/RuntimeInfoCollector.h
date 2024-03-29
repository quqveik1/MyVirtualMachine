#pragma once

#include <deque>

#include "RuntimeCommandInfo.h"
#include "Processor.h"

class RuntimeInfoCollector
{
    std::deque<RuntimeCommandInfo> commands;

    const int HistoryLen       = 32;
    const int PrintByteDataLen = 12;

    Processor& processor;

public:

    RuntimeInfoCollector(Processor& _processor);

    std::deque<RuntimeCommandInfo>& getCommands() { return commands; }

    void addLastCommand(int commandFileStart, int commandData);

    ErrorCode onError();
    ErrorCode print  ();

private:
    ErrorCode disassemble (std::wstring& ans, RuntimeCommandInfo& info);
    void pushCommand(RuntimeCommandInfo& info);
};