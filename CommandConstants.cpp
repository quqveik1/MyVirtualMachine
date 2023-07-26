#pragma once

#include "CommandConstants.h"

#include "StringViewExtension.cpp"

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

    //!!!
    else if (svcmp(commandName, neg_str) == 0)
    {
        res = neg_num;
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

    ans = commandNames[commandNum];

    return WellCode;
}

void initCommandsNameArr()
{
    commandNames =
    {
        /*0*/   L"innerCall",
                L"hlt",
                L"in",
                L"out",
                L"push",
                L"add",
                L"sub",
                L"mul",
                L"div",
                L"pop",
                L"jmp",
                L"ja",
                L"jae",
                L"jb",
                L"jbe",
                L"je",
                L"jne",
                L"sqrt",
                L"db",
                L"word",
                L"call",
                L"ret",
                L"neg"
    };
}

bool isCommandNumValid(int num)
{
    if (0 < num && num <= cCommands)
    {
        return true;
    }
    return false;
}

void _checkCommandsHealth()
{
    int num = 0;

    switch (num)
    {
    case innerCall_num:
    case hlt_num:
    case in_num:
    case out_num:
    case push_num:
    case add_num:
    case sub_num:
    case mul_num:
    case div_num:

    case pop_num:

    case jmp_num:
    case ja_num:
    case jae_num:
    case jb_num:
    case jbe_num:
    case je_num:
    case jne_num:

    case sqrt_num:

    case db_num:

    case word_num:

    case call_num:
    case ret_num:

    case neg_num:  //!!!

    default:
        break;
    }
}