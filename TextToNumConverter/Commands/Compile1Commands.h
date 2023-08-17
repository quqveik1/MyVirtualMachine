#pragma once
#include <string>

#include "../IR/IR.h"
#include "../Constants/ErrorCode.h"

using COMMAND1COMPILETYPE = 
ErrorCode (*)                            (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode default_1compile               (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode out_1compile                   (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode convertArg    (double& ans, std::wstring_view& arg, bool* isNumber, bool* reg, int base/* = 10*/);
void findBrackets       (std::wstring_view& data, int& startPos, int& endPos);
bool editDataForBrackets(std::wstring_view& data);

ErrorCode saveSmallExpr                  (CommandIR& commandIR, int commandNum, std::wstring_view& data, int base = 10);
ErrorCode push_1compile                  (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode pop_1compile                   (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

bool isJmpWord          (std::wstring_view& arg);
ErrorCode saveWordExpression             (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);
ErrorCode jmp_1compile                   (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

size_t cDeletedSymAfterCompilation(const std::wstring_view& str);
ErrorCode writeStrInData                 (CommandIR& commandIR, std::wstring_view& data, size_t firstQuotePos, size_t secondQuotePos);
ErrorCode db_1compile                    (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode word_1compile                  (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);

ErrorCode rdsys_1compile                 (CommandIR& commandIR, int commandNum, std::wstring_view& data, IR& ir);