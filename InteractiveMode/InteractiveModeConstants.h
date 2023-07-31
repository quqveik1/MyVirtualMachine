#pragma once

#include <string>

#include "InteractiveCommands.h"

const std::wstring q_str = L"q";
const std::wstring quit_str = L"quit";
const std::wstring i_str = L"info";
const std::wstring info_str = L"i";    
const std::wstring bt_str = L"bt";
const std::wstring backtrace_str = L"backtrace"; 
const std::wstring d_str = L"d";
const std::wstring disassemble_str = L"disassemble";

INTERACTVECOMMAND getInteractiveCommand(std::wstring& command);