#pragma once
#include <string>

#include "CommandIR.h"
#include "IR.h"
#include "CommandIR.h"

using COMMAND1COMPILETYPE = int (*)(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

int default_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

int out_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

bool isRegister(std::wstring_view& arg);
double convertArg(std::wstring_view& arg, bool* number, bool* reg, int base = 10);
void findBrackets(std::wstring_view& data, int& startPos, int& endPos);
bool editDataForBrackets(std::wstring_view& data);
int saveSmallExpr(CommandIR& commandIR, int commandNum, std::wstring_view& data, int base = 10);
int push_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

int pop_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

bool isJmpWord(std::wstring_view& arg);
int saveWordExpression(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);
int jmp_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

size_t cDeletedSymAfterCompilation(const std::wstring_view& str);
int writeStrInData(CommandIR& commandIR, std::wstring_view& data, size_t firstQuotePos, size_t secondQuotePos);
int db_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

int word_1compile(CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);
