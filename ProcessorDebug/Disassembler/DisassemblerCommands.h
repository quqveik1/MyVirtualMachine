#pragma once

#include <string>

#include "..\RuntimeCommandInfo.h"
#include "..\..\Processor\Processor.h"
#include "../../Constants/ErrorCode.h"

using DISASSEMBLERCOMMANDS =            
ErrorCode (*)                                        (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode defaultOnlyName_dissassemblerCommand       (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode defaultSmallExpression                     (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine, int constantBase = 10, int* finishPos = nullptr);
ErrorCode defaultSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode hexSaveSmallExpression_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode jmp_dissassemblerCommand                   (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode ret_dissassemblerCommand                   (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

ErrorCode rdsys_dissassemblerCommand                 (Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);