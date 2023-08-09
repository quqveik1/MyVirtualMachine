#pragma once

#include "CommandConstants.h"

#include "../Common/StringViewExtension.cpp"

std::vector<std::wstring> commandNames;

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

    else if (svcmp(commandName, word_str) == 0)
    {
        res = word_num;
    }

    else if (svcmp(commandName, call_str) == 0)
    {
        res = call_num;
    }

    else if (svcmp(commandName, ret_str) == 0)
    {
        res = ret_num;
    }
    else if (svcmp(commandName, neg_str) == 0)
    {
        res = neg_num;
    }
    else if (svcmp(commandName, imto_str) == 0)
    {
        res = imto_num;
    }
    else if (svcmp(commandName, setpxl_str) == 0)
    {
        res = setpxl_num;
    }
    else if (svcmp(commandName, rdsys_str) == 0)
    {
        res = rdsys_num;
    }

    return res;
}

int getCommandName(int commandNum, std::wstring& ans)
{
    bool res = isCommandNumValid(commandNum);

    if(!res)
    {
        return DisassemblyNameError;
    }

    switch (commandNum)
    {
    case hlt_num:
        ans = hlt_str;
        break;
    case in_num:
        ans = in_str;
        break;
    case out_num:
        ans = out_str;
        break;
    case push_num:
        ans = push_str;
        break;
    case add_num:
        ans = add_str;
        break;
    case sub_num:
        ans = sub_str;
        break;
    case mul_num:
        ans = mul_str;
        break;
    case div_num:
        ans = div_str;
        break;
    case pop_num:
        ans = pop_str;
        break;
    case jmp_num:
        ans = jmp_str;
        break;
    case ja_num:
        ans = ja_str;
        break;
    case jae_num:
        ans = jae_str;
        break;
    case jb_num:
        ans = jb_str;
        break;
    case jbe_num:
        ans = jbe_str;
        break;
    case je_num:
        ans = je_str;
        break;
    case jne_num:
        ans = jne_str;
        break;
    case sqrt_num:
        ans = sqrt_str;
        break;
    case db_num:
        ans = db_str;
        break;
    case word_num:
        ans = word_str;
        break;
    case call_num:
        ans = call_str;
        break;
    case ret_num:
        ans = ret_str;
        break;
    case neg_num:
        ans = neg_str;
        break;
    case imto_num:
        ans = imto_str;
        break;
    case setpxl_num:
        ans = setpxl_str;
        break;
    case rdsys_num:
        ans = rdsys_str;
        break;

    default:
        break;
    
    }

    return WellCode;
}

bool isCommandNumValid(int num)
{
    if (0 < num && num <= cCommands)
    {
        return true;
    }
    return false;
}