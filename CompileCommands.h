#pragma once
#include <string>

using COMMANDCOMPILETYPE = int (*)(std::wstring_view& data, char** binaryData);

int push_compile(std::wstring_view& data, char** binaryData);
