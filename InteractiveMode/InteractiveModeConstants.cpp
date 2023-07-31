#pragma once

#include "InteractiveModeConstants.h"

INTERACTVECOMMAND getInteractiveCommand(std::wstring& command)
{
    if (command == quit_str || command == q_str)
    {
        return quit_command;
    }
    if (command == info_str || command == i_str)
    {
        return info_command;
    }
    if (command == bt_str || command == backtrace_str)
    {
        return backtrace_command;
    }
    if (command == d_str || command == disassemble_str)
    {
        return disassemble_command;
    }

    return nullptr;
}