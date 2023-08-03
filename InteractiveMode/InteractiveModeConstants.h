#pragma once

#include <string>

#include "InteractiveCommands.h"

const std::wstring quit_str[] = { L"quit", L"q" };
const std::wstring continue_str[] = { L"continue", L"c" };
const std::wstring info_str[] = { L"info", L"i" };
const std::wstring backtrace_str[] = { L"backtrace", L"bt" };
const std::wstring disassemble_str[] = { L"disassemble", L"d" };
const std::wstring examine_str[] = { L"examine", L"x" };
const std::wstring set_str[] = { L"set", L"s" };
const std::wstring set_stack_str[] = { L"set_stack", L"ss" };
const std::wstring set_backtrace_str[] = { L"set_backtrace", L"sb" };
const std::wstring jump_interactive_str[] = { L"jump", L"j" };
const std::wstring breakpoint_intractive_str[] = { L"break", L"b" };
const std::wstring delete_breakpoint_intractive_str[] = { L"delete", L"del" };

template<typename S>
INTERACTVECOMMAND getInteractiveCommand(S& command);
template<typename S>
bool hasThisCommand(const std::wstring arr[], S& command);