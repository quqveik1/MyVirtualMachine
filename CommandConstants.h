#pragma once

#include <string>

const int COMMANDSVERSION = 9;

const int cCommands = 19;

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

//------------------------------------------------------------------

const int innerCall_num = 0;

const int hlt_num = 1;

const int in_num = 2;
const int out_num = 3;
const int push_num = 4;

const int add_num = 5;
const int sub_num = 6;
const int mul_num = 7;
const int div_num = 8;

const int pop_num = 9;

const int jmp_num = 10;
const int ja_num = 11;
const int jae_num = 12;
const int jb_num = 13;
const int jbe_num = 14;
const int je_num = 15;
const int jne_num = 16;

const int sqrt_num = 17;

const int db_num = 18;

const int word_num = 19;

//------------------------------------------------------------------

int getCommandNum(std::wstring_view& commandName, size_t commandSize = std::wstring_view::npos);
bool isCommandNumValid(int num);
                      
//------------------------------------------------------------------

const int WellCode = 0;
const int CommandBreakCode = -1;

const int CommandReadErrorCode = -2;
const int CommandEndFileErrorCode = -3;

const int FileHeaderReadErrorCode = -4;   
const int CommandWriteDataCode = -5;
const int CommandRecognizeError = -6;

const int MachineCodeOutOfBound = -7;
const int EmptyStackGetError = -8;

const int NoQuoteDBError = -9;
const int CommandDataReadError = -10;