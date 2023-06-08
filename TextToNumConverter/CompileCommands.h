#pragma once
#include <string>
#include "CompileData.h"

using COMMANDCOMPILETYPE = int (*)(CompileData& compileData, int commandNum, std::wstring_view& data);

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

int convertArgToInt(std::wstring_view& arg, bool* constant, bool* reg);
void findBrackets(std::wstring_view& data, int& startPos, int& endPos);
bool editDataForBrackets(std::wstring_view& data);
int saveSmallExpr(CompileData& compileData, int commandNum, std::wstring_view& data);
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
int pop_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
