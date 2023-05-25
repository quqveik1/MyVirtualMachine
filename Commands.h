//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "RuntimeData.h"
#include "CommandConstants.h"

int in_command(RuntimeData& appData, char* commandData);
int out_command(RuntimeData& appData, char* commandData);
int push_command(RuntimeData& appData, char* commandData);

int hlt_command(RuntimeData& appData, char* commandData);

int add_command(RuntimeData& appData, char* commandData);
int sub_command(RuntimeData& appData, char* commandData);
int mul_command(RuntimeData& appData, char* commandData);
int div_command(RuntimeData& appData, char* commandData);

using COMMANDTYPE = int (*)(RuntimeData& appData, char* commandData);

const int COMMANDSVERSION = 1;