#pragma once

#include <queue>

#include "RuntimeCommandInfo.h"
#include "Processor.h"

class RuntimeInfoCollector
{
    std::queue<RuntimeCommandInfo> commands;

    const int HistoryLen = 16;

    Processor& processor;

public:

    RuntimeInfoCollector(Processor& _processor);

    std::queue<RuntimeCommandInfo>& getCommands() { return commands; }

    void pushCommand(RuntimeCommandInfo& info);

    void addLastCommand(int commandFileStart, int commandNum);

    int print();

private:
    int disassemble(std::wstring& ans, RuntimeCommandInfo& info);
};