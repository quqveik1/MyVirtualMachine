#pragma once

#include <map>
#include <string>

#include "ErrorCode.h"

enum SystemComponents
{
    error      = -1,
    vsizex_num = 0,
    vsizey_num = 1
};

const std::wstring vsizex_str = L"vsizex";
const std::wstring vsizey_str = L"vsizey";


template <typename S>
SystemComponents getComponentNumFromStr(S& str);

ErrorCode getComponentStrFromNum(SystemComponents num, std::wstring& str);
