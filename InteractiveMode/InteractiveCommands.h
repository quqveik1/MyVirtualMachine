#pragma once

#include "../Constants/ErrorCode.h"
#include "../Processor/Processor.h"
#include "InteractiveCode.h"

using INTERACTVECOMMAND = ErrorCode(*)(Processor& processor, InteractiveCode& code, std::wstring_view& data);

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode continue_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);

ErrorCode info_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode info_breakpoint_command(Processor& processor);
ErrorCode backtrace_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode disassemble_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
void printRuntimeData(Processor& processor);
void printRuntimeInfoDissassembler(Processor& processor);
void printCallStack(Processor& processor);
void printRegisters(Processor& processor);

ErrorCode delete_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);

ErrorCode examine_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode set_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode stack_universal_command(Processor& processor, InteractiveCode& code, std::wstring_view& data, StackVector& stackVector, bool needToConvert = true);
ErrorCode set_stack_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);
ErrorCode set_backtrace_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);

ErrorCode jump_interactive_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);

ErrorCode breakpoint_interactive_command(Processor& processor, InteractiveCode& code, std::wstring_view& data);