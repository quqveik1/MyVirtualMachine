#pragma once

#include "CommandConstants.h"

#include "StringViewExtension.cpp"

int getCommandNum(std::wstring_view& commandName, size_t commandSize/* = std::wstring_view::npos*/)
{
    int res = CommandRecognizeError;

    if (commandSize == std::wstring_view::npos)
    {
        commandSize = commandName.size();
    }

    if (commandSize == 0) return res;
    if (svcmp(commandName, in_str) == 0)
    {
        res = in_num;
    }

    else if (svcmp(commandName, out_str) == 0)
    {
        res = out_num;
    }

    else if (svcmp(commandName, push_str) == 0)
    {
        res = push_num;
    }

    else if (svcmp(commandName, hlt_str) == 0)
    {
        res = hlt_num;
    }

    else if (svcmp(commandName, add_str) == 0)
    {
        res = add_num;
    }

    else if (svcmp(commandName, sub_str) == 0)
    {
        res = sub_num;
    }

    else if (svcmp(commandName, mul_str) == 0)
    {
        res = mul_num;
    }

    else if (svcmp(commandName, div_str) == 0)
    {
        res = div_num;
    }

    else if (svcmp(commandName, pop_str) == 0)
    {
        res = pop_num;
    }

    else if (svcmp(commandName, jmp_str) == 0)
    {
        res = jmp_num;
    }

    else if (svcmp(commandName, ja_str) == 0)
    {
        res = ja_num;
    }

    else if (svcmp(commandName, jae_str) == 0)
    {
        res = jae_num;
    }

    else if (svcmp(commandName, jb_str) == 0)
    {
        res = jb_num;
    }

    else if (svcmp(commandName, jbe_str) == 0)
    {
        res = jbe_num;
    }

    else if (svcmp(commandName, je_str) == 0)
    {
        res = je_num;
    }

    else if (svcmp(commandName, jne_str) == 0)
    {
        res = jne_num;
    }

    else if (svcmp(commandName, sqrt_str) == 0)
    {
        res = sqrt_num;
    }

    else if (svcmp(commandName, db_str) == 0)
    {
        res = db_num;
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