#pragma once
#include <string>
#include "CompileData.h"

using COMMANDCOMPILETYPE = int (*)(CompileData& compileData, int commandNum, std::wstring_view& data);

int default_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

int out_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

bool isRegister(std::wstring_view& arg);
double convertArg(std::wstring_view& arg, bool* number, bool* reg, int base = 10);
void findBrackets(std::wstring_view& data, int& startPos, int& endPos);
bool editDataForBrackets(std::wstring_view& data);
int saveSmallExpr(CompileData& compileData, int commandNum, std::wstring_view& data, int base = 10);
int push_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

int pop_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

bool isJmpWord(std::wstring_view& arg);
int jmp_compile(CompileData& compileData, int commandNum, std::wstring_view& data);

size_t cDeletedSymAfterCompilation(const std::wstring_view& str);
int writeStrInData(CompileData& compileData, std::wstring_view& data, size_t firstQuotePos, size_t secondQuotePos);
int db_compile(CompileData& compileData, int commandNum, std::wstring_view& data);
