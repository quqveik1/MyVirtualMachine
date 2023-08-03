#pragma once

#include <string>

#include "ErrorCode.h"

const int COMMANDSVERSION = 15;

const int cCommands = 25;

const std::wstring hlt_str = L"hlt";

const std::wstring in_str = L"in";
const std::wstring out_str = L"out";
const std::wstring push_str = L"push";

const std::wstring add_str = L"add";
const std::wstring sub_str = L"sub";
const std::wstring mul_str = L"mul";
const std::wstring div_str = L"div";

const std::wstring pop_str = L"pop";

const std::wstring jmp_str = L"jmp";
const std::wstring ja_str = L"ja";
const std::wstring jae_str = L"jae";
const std::wstring jb_str = L"jb";
const std::wstring jbe_str = L"jbe";
const std::wstring je_str = L"je";
const std::wstring jne_str = L"jne";

const std::wstring sqrt_str = L"sqrt";

const std::wstring db_str = L"db";

const std::wstring word_str = L"word";

const std::wstring call_str = L"call";
const std::wstring ret_str = L"ret";

const std::wstring neg_str = L"neg";  //!!!

const std::wstring imto_str = L"imto";  //!!!
const std::wstring breakpoint_str = L"breakpoint";  //!!!

const std::wstring pixel_str = L"pixel";

//------------------------------------------------------------------

enum CommandNums
{
    innerCall_num = 0,
    hlt_num = 1,
    in_num = 2,
    out_num = 3,
    push_num = 4,
    add_num = 5,
    sub_num = 6,
    mul_num = 7,
    div_num = 8,

    pop_num = 9,

    jmp_num = 10,
    ja_num = 11,
    jae_num = 12,
    jb_num = 13,
    jbe_num = 14,
    je_num = 15,
    jne_num = 16,

    sqrt_num = 17,

    db_num = 18,

    word_num = 19,

    call_num = 20,
    ret_num = 21,

    neg_num = 22,  
    imto_num = 23,  
    breakpoint_num = 24,
    pixel_num = 25
};

//------------------------------------------------------------------

int getCommandNum(std::wstring_view& commandName, size_t commandSize = std::wstring_view::npos);
bool isCommandNumValid(int num);
int getCommandName(int commandNum, std::wstring& ans);
void initCommandsNameArr();
void _checkCommandsHealth();
                      
//------------------------------------------------------------------