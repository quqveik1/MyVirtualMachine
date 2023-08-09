#pragma once

#include <deque>

#include "RuntimeCommandInfo.h"
#include "Processor.h"

class RuntimeInfoCollector
{
    std::deque<RuntimeCommandInfo> commands;

    const int HistoryLen       = 16;
    const int PrintByteDataLen = 8;

    Processor& processor;

public:

    RuntimeInfoCollector(Processor& _processor);

    std::deque<RuntimeCommandInfo>& getCommands() { return commands; }

    void addLastCommand(int commandFileStart, int commandData);

    int onError();
    int print  ();

private:
    int disassemble (std::wstring& ans, RuntimeCommandInfo& info);
    void pushCommand(RuntimeCommandInfo& info);
};