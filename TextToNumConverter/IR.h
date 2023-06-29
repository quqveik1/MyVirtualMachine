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
};