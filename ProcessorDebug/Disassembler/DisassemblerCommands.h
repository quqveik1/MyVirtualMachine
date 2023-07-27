#pragma once

#include <string>
#include "..\RuntimeCommandInfo.h"

using DISASSEMBLERCOMMANDS = int (*)(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

int defaultOnlyName_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

int defaultSmallExpression(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine, int constantBase = 10, int* finishPos = nullptr);
int defaultSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

int hexSaveSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

int jmp_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);