#pragma once

#include <vector>

#include "CommandIR.h"

struct IR
{
    IR();

private:
    std::vector<CommandIR> commands;

public:
    std::vector<CommandIR>& getCommands() { return commands; };
    CommandIR& getCommand(int i);
    CommandIR& getActiveCommand() { return commands[commands.size() - 1]; };

    void addNewCommand() { commands.resize(commands.size() + 1); }

};