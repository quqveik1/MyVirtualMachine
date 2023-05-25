#pragma once

const int cCommands = 8;

#define hlt_str L"hlt"

#define in_str L"in"
#define out_str L"out"
#define push_str L"push"

#define add_str L"add"
#define sub_str L"sub"
#define mul_str L"mul"
#define div_str L"div"

//------------------------------------------------------------------

#define commandError_num -1

#define hlt_num 1

#define in_num   2
#define out_num  3
#define push_num 4

#define add_num 5
#define sub_num 6
#define mul_num 7
#define div_num 8

//------------------------------------------------------------------

bool isCommandNumValid(int num)
{
    if (0 <= num && num <= cCommands)
    {
        return true;
    }
    return false;
}
                      
//------------------------------------------------------------------

#define commandError_strnum L"-1"

#define hlt_strnum L"1"

#define in_strnum   L"2"
#define out_strnum  L"3"
#define push_strnum L"4"

#define add_strnum L"5"
#define sub_strnum L"6"
#define mul_strnum L"7"
#define div_strnum L"8"

//------------------------------------------------------------------

const int WellCode = 0;
const int CommandBreakCode = -1;

const int CommandReadErrorCode = -2;
const int CommandEndFileErrorCode = -3;