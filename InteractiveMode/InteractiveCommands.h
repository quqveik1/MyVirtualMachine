#pragma once

#include "../Constants/ErrorCode.h"
#include "../Processor/Processor.h"
#include "InteractiveCode.h"

using INTERACTVECOMMAND = ErrorCode(*)(Processor& processor, InteractiveCode& code, std::wstring& data);

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring& data);

ErrorCode info_command(Processor& processor, InteractiveCode& code, std::wstring& data);
ErrorCode backtrace_command(Processor& processor, InteractiveCode& code, std::wstring& data);
ErrorCode disassemble_command(Processor& processor, InteractiveCode& code, std::wstring& data);
void printRuntimeData(Processor& processor);
void printRuntimeInfoDissassembler(Processor& processor);
void printCallStack(Processor& processor);
void printRegisters(Processor& processor);