#pragma once
#include <string>

using COMMANDCOMPILETYPE = char* (*)(std::wstring_view& data);

char* push_compile(std::wstring_view& data);
