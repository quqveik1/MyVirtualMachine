#pragma once

#include "DisassemblerCommands.h"

#include "..\..\CommandConstants.h"

int defaultOnlyName_dissassemblerCommand(Processor& processor, RuntimeCommandInfo& commandInfo, std::wstring& originalLine)
{
    return getCommandName(commandInfo.commandNum, originalLine);
}