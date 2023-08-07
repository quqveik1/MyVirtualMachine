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
    else if (svcmp(commandName, pixel_str) == 0)
    {
        res = pixel_num;
    }
    else if (svcmp(commandName, si_str) == 0)
    {
        res = si_num;
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
    case innerCall_num:
        ans = L"inner_call";
        break;
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
    case breakpoint_num:
        ans = breakpoint_str;
        break;
    case pixel_num:
        ans = pixel_str;
        break;
    case si_num:
        ans = si_str;
        break;

    default:
        break;
    
    }

    return WellCode;
}

void initCommandsNameArr()
{
    commandNames =
    {
        /*0*/   L"inner call",
                hlt_str,
                in_str,
                out_str,
                push_str,
                add_str,
                sub_str,
                mul_str,
                div_str,
                pop_str,
                jmp_str,
                ja_str,
                jae_str,
                jb_str,
                jbe_str,
                je_str,
                jne_str,
                sqrt_str,
                db_str,
                word_str,
                call_str,
                ret_str,
                neg_str,
                imto_str,
                breakpoint_str,
                pixel_str,
                si_str
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

    case neg_num:
    case imto_num:
    case breakpoint_num:
    case pixel_num:
    case si_num:

    default:
        break;
    }
}