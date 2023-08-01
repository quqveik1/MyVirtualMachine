#pragma once

#include <string>

#include "InteractiveCommands.h"

const std::wstring quit_str[] = { L"quit", L"q" };
const std::wstring info_str[] = { L"info", L"i" };
const std::wstring backtrace_str[] = { L"backtrace", L"bt" };
const std::wstring disassemble_str[] = { L"disassemble", L"d" };
const std::wstring examine_str[] = { L"examine", L"x" };
const std::wstring set_str[] = { L"set", L"s" };
const std::wstring jump_interactive_str[] = { L"jump", L"j" };

INTERACTVECOMMAND getInteractiveCommand(std::wstring& command);
bool hasThisCommand(const std::wstring arr[], std::wstring& command);