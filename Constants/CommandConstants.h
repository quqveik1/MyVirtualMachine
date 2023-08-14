#pragma once

#include <string>

#include "ErrorCode.h"

const int COMMANDSVERSION = 17;

const int cCommands = 256;

const std::wstring_view hlt_str    = L"hlt";

const std::wstring_view in_str     = L"in";
const std::wstring_view out_str    = L"out";
const std::wstring_view push_str   = L"push";

const std::wstring_view add_str    = L"add";
const std::wstring_view sub_str    = L"sub";
const std::wstring_view mul_str    = L"mul";
const std::wstring_view div_str    = L"div";

const std::wstring_view pop_str    = L"pop";

const std::wstring_view jmp_str    = L"jmp";
const std::wstring_view ja_str     = L"ja";
const std::wstring_view jae_str    = L"jae";
const std::wstring_view jb_str     = L"jb";
const std::wstring_view jbe_str    = L"jbe";
const std::wstring_view je_str     = L"je";
const std::wstring_view jne_str    = L"jne";

const std::wstring_view sqrt_str   = L"sqrt";
const std::wstring_view sin_str    = L"sin";

const std::wstring_view db_str     = L"db";

const std::wstring_view word_str   = L"word";

const std::wstring_view call_str   = L"call";
const std::wstring_view ret_str    = L"ret";

const std::wstring_view neg_str    = L"neg";

const std::wstring_view into_str   = L"into";

const std::wstring_view setpxl_str = L"setpxl";
const std::wstring_view rdsys_str  = L"rdsys";

//------------------------------------------------------------------

enum CommandNums
{
    hlt_num    = 0xF4,
    in_num     = 0x2,
    out_num    = 0x3,
    push_num   = 0x06,
    add_num    = 0x00,
    sub_num    = 0x28,
    mul_num    = 0xF6,
    div_num    = 0xF7,
    pop_num    = 0x07,
    jmp_num    = 0xEB,
    ja_num     = 0xEC,
    jae_num    = 0xED,
    jb_num     = 0xEE,
    jbe_num    = 0xEF,
    je_num     = 0xF0,
    jne_num    = 0xF1,
    sqrt_num   = 0x17,
    sin_num    = 0x18,
    db_num     = 0x30,
    word_num   = 0x31,
    call_num   = 0xE8,
    ret_num    = 0xC2,
    neg_num    = 0xF8,
    into_num   = 0xCE,
    setpxl_num = 0x25,
    rdsys_num  = 0x27
};

//------------------------------------------------------------------

ErrorCode getCommandNum(int& commandNum, const std::wstring_view& commandName);
bool isCommandNumValid(int num);
ErrorCode getCommandName    (int commandNum, std::wstring& ans);
                      
//------------------------------------------------------------------