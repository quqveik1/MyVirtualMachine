#pragma once

const int cCommands = 11;

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

//------------------------------------------------------------------


int getCommandNum(std::wstring_view& commandName);
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