#pragma once
#include <string>
#include "CompileData.h"

using COMMANDCOMPILETYPE = int (*)(CompileData& compileData, int commandNum, std::wstring_view& data);

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
int pop_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
