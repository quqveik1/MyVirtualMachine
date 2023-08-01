#pragma once

#include "InteractiveModeConstants.h"

INTERACTVECOMMAND getInteractiveCommand(std::wstring& command)
{
    if (hasThisCommand(quit_str, command))
    {
        return quit_command;
    }
    if (hasThisCommand(continue_str, command))
    {
        return continue_command;
    }
    if (hasThisCommand(info_str, command))
    {
        return info_command;
    }
    if (hasThisCommand(backtrace_str, command))
    {
        return backtrace_command;
    }
    if (hasThisCommand(disassemble_str, command))
    {
        return disassemble_command;
    }
    if (hasThisCommand(examine_str, command))
    {
        return examine_command;
    }
    if (hasThisCommand(set_str, command))
    {
        return set_command;
    }
    if (hasThisCommand(set_stack_str, command))
    {
        return set_stack_command;
    }
    if (hasThisCommand(set_backtrace_str, command))
    {
        return set_backtrace_command;
    }
    if (hasThisCommand(jump_interactive_str, command))
    {
        return jump_interactive_command;
    }

    return nullptr;
}

bool hasThisCommand(const std::wstring arr[], std::wstring& command)
{
    for(int i = 0; i < 2; i++)
    {
        if(arr[i] == command)
        {
            return true;
        }
    }

    return false;
}