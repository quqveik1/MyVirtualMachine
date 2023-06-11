#pragma once

#include "CommandConstants.h"

int getCommandNum(std::wstring_view& commandName)
{
    int res = CommandRecognizeError;
    if (_wcsnicmp(commandName.data(), in_str.c_str(), commandName.size()) == 0)
    {
        res = in_num;
    }

    else if (_wcsnicmp(commandName.data(), out_str.c_str(), commandName.size()) == 0)
    {
        res = out_num;
    }

    else if (_wcsnicmp(commandName.data(), push_str.c_str(), commandName.size()) == 0)
    {
        res = push_num;
    }

    else if (_wcsnicmp(commandName.data(), hlt_str.c_str(), commandName.size()) == 0)
    {
        res = hlt_num;
    }

    else if (_wcsnicmp(commandName.data(), add_str.c_str(), commandName.size()) == 0)
    {
        res = add_num;
    }

    else if (_wcsnicmp(commandName.data(), sub_str.c_str(), commandName.size()) == 0)
    {
        res = sub_num;
    }

    else if (_wcsnicmp(commandName.data(), mul_str.c_str(), commandName.size()) == 0)
    {
        res = mul_num;
    }

    else if (_wcsnicmp(commandName.data(), div_str.c_str(), commandName.size()) == 0)
    {
        res = div_num;
    }

    else if (_wcsnicmp(commandName.data(), pop_str.c_str(), commandName.size()) == 0)
    {
        res = pop_num;
    }

    else if (_wcsnicmp(commandName.data(), jmp_str.c_str(), commandName.size()) == 0)
    {
        res = jmp_num;
    }

    else if (_wcsnicmp(commandName.data(), ja_str.c_str(), commandName.size()) == 0)
    {
        res = ja_num;
    }    

    else if (_wcsnicmp(commandName.data(), jae_str.c_str(), commandName.size()) == 0)
    {
        res = jae_num;
    }    

    else if (_wcsnicmp(commandName.data(), jb_str.c_str(), commandName.size()) == 0)
    {
        res = jb_num;
    }    

    else if (_wcsnicmp(commandName.data(), jbe_str.c_str(), commandName.size()) == 0)
    {
        res = jbe_num;
    }    

    else if (_wcsnicmp(commandName.data(), je_str.c_str(), commandName.size()) == 0)
    {
        res = je_num;
    }    

    else if (_wcsnicmp(commandName.data(), jne_str.c_str(), commandName.size()) == 0)
    {
        res = jne_num;
    }

    return res;
}

bool isCommandNumValid(int num)
{
    if (0 < num && num <= cCommands)
    {
        return true;
    }
    return false;
}