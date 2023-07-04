#pragma once

#include <vector>

#include "CommandIR.h"
#include "LabelSearchIR.h"

struct IR
{
    IR();

private:
    std::vector<CommandIR> commands;

    LabelSearchIR labelSearchIR;

public:
    std::vector<CommandIR>& getCommands() { return commands; };
    CommandIR& getCommand(int i);
    CommandIR& getActiveCommand() { return commands[commands.size() - 1]; };
    size_t getActiveCommandNum() { return commands.size() - 1; };
    LabelSearchIR& getLabelSearchIR() { return labelSearchIR; };

    void addNewCommand() { commands.resize(commands.size() + 1); }

    int finishIntermediateWork();
};