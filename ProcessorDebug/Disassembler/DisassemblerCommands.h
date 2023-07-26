#pragma once

#include <string>
#include "..\RuntimeCommandInfo.h"

using DISASSEMBLERCOMMANDS = int (*)(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);

int defaultOnlyName_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine);