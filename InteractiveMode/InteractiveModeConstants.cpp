#pragma once

#include "InteractiveModeConstants.h"

INTERACTVECOMMAND getInteractiveCommand(std::wstring& command)
{
    if (hasThisCommand(quit_str, command))
    {
        return quit_command;
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