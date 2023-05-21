//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "RuntimeData.h"
#include "CommandConstants.h"

int in_command(RuntimeData& appData, std::wstring_view& commandData);
int out_command(RuntimeData& appData, std::wstring_view& commandData);
int push_command(RuntimeData& appData, std::wstring_view& commandData);

int hlt_command(RuntimeData& appData, std::wstring_view& commandData);

int add_command(RuntimeData& appData, std::wstring_view& commandData);
int sub_command(RuntimeData& appData, std::wstring_view& commandData);
int mul_command(RuntimeData& appData, std::wstring_view& commandData);
int div_command(RuntimeData& appData, std::wstring_view& commandData);

using COMMANDTYPE = int (*)(RuntimeData& appData, std::wstring_view& commandData);