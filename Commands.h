//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "RuntimeData.h"
#include "CommandConstants.h"
#include "Processor.h"

int in_command(Processor& processor, int codedCommandNum);
int out_command(Processor& processor, int codedCommandNum);
int push_command(Processor& processor, int codedCommandNum);

int hlt_command(Processor& processor, int codedCommandNum);

int add_command(Processor& processor, int codedCommandNum);
int sub_command(Processor& processor, int codedCommandNum);
int mul_command(Processor& processor, int codedCommandNum);
int div_command(Processor& processor, int codedCommandNum);

int pop_command(Processor& processor, int codedCommandNum);

using COMMANDTYPE = int (*)(Processor& processor, int codedCommandNum);

const int COMMANDSVERSION = 2;