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

const std::wstring_view db_str     = L"db";

const std::wstring_view word_str   = L"word";

const std::wstring_view call_str   = L"call";
const std::wstring_view ret_str    = L"ret";

const std::wstring_view neg_str    = L"neg";

const std::wstring_view imto_str   = L"imto";

const std::wstring_view setpxl_str = L"setpxl";
const std::wstring_view rdsys_str  = L"rdsys";

//------------------------------------------------------------------

enum CommandNums
{
    hlt_num    = 1,
    in_num     = 2,
    out_num    = 3,
    push_num   = 4,
    add_num    = 5,
    sub_num    = 6,
    mul_num    = 7,
    div_num    = 8,

    pop_num    = 9,

    jmp_num    = 10,
    ja_num     = 11,
    jae_num    = 12,
    jb_num     = 13,
    jbe_num    = 14,
    je_num     = 15,
    jne_num    = 16,

    sqrt_num   = 17,

    db_num     = 18,

    word_num   = 19,

    call_num   = 20,
    ret_num    = 21,

    neg_num    = 22,  
    imto_num   = 23,  

    setpxl_num = 25,
    rdsys_num  = 26
};

//------------------------------------------------------------------

int getCommandNum     (std::wstring_view& commandName, size_t commandSize = std::wstring_view::npos);
bool isCommandNumValid(int num);
int getCommandName    (int commandNum, std::wstring& ans);
                      
//------------------------------------------------------------------