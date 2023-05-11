//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include "RuntimeData.h"

#define RuntimeAppData RuntimeData

int in_command(RuntimeAppData& appData, std::string_view& commandData);
int out_command(RuntimeAppData& appData, std::string_view& commandData);
int push_command(RuntimeAppData& appData, std::string_view& commandData);

int hlt_command(RuntimeAppData& appData, std::string_view& commandData);

int add_command(RuntimeAppData& appData, std::string_view& commandData);
int sub_command(RuntimeAppData& appData, std::string_view& commandData);
int mul_command(RuntimeAppData& appData, std::string_view& commandData);
int div_command(RuntimeAppData& appData, std::string_view& commandData);