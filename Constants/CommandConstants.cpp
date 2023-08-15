#pragma once

#include "CommandConstants.h"

#include "../Common/StringViewExtension.cpp"

std::vector<std::wstring> commandNames;

ErrorCode getCommandNum(CommandType& commandNum, const std::wstring_view& commandName)
{
    if (commandName.size() == 0) return ErrorCode::CommandRecognizeError;

    if (commandName == in_str)
    {
        commandNum = in_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == out_str)
    {
        commandNum = out_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == push_str)
    {
        commandNum = push_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == hlt_str)
    {
        commandNum = hlt_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == add_str)
    {
        commandNum = add_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == sub_str)
    {
        commandNum = sub_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == mul_str)
    {
        commandNum = mul_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == div_str)
    {
        commandNum = div_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == pop_str)
    {
        commandNum = pop_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == jmp_str)
    {
        commandNum = jmp_num;
        return ErrorCode::WellCode;
    }

    else if (commandName == ja_str)
    {
        commandNum = ja_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == jae_str)
    {
        commandNum = jae_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == jb_str)
    {
        commandNum = jb_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == jbe_str)
    {
        commandNum = jbe_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == je_str)
    {
        commandNum = je_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == jne_str)
    {
        commandNum = jne_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == sqrt_str)
    {
        commandNum = sqrt_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == sin_str)
    {
        commandNum = sin_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == db_str)
    {
        commandNum = db_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == word_str)
    {
        commandNum = word_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == call_str)
    {
        commandNum = call_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == ret_str)
    {
        commandNum = ret_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == neg_str)
    {
        commandNum = neg_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == into_str)
    {
        commandNum = into_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == setpxl_str)
    {
        commandNum = setpxl_num;
        return ErrorCode::WellCode;
    }
    else if (commandName == rdsys_str)
    {
        commandNum = rdsys_num;
        return ErrorCode::WellCode;
    }

    return ErrorCode::CommandRecognizeError;
}

ErrorCode getCommandName(CommandType commandNum, std::wstring& ans)
{
    bool res = isCommandNumValid(commandNum);

    if(!res)
    {
        return ErrorCode::DisassemblyNameError;
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
    case sin_num:
        ans = sin_str;
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
    case into_num:
        ans = into_str;
        break;
    case setpxl_num:
        ans = setpxl_str;
        break;
        break;
    case rdsys_num:
        ans = rdsys_str;
        break;

    default:
        return ErrorCode::CommandRecognizeError;
        break;
    }

    return ErrorCode::WellCode;
}

bool isCommandNumValid(CommandType num)
{
    if (0 <= num && num <= cCommands)
    {
        return true;
    }
    return false;
}