//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "RuntimeData.h"
#include "CommandConstants.h"
#include "Processor.h"

int in_command(Processor& processor);
int out_command(Processor& processor);
int push_command(Processor& processor);

int hlt_command(Processor& processor);

int add_command(Processor& processor);
int sub_command(Processor& processor);
int mul_command(Processor& processor);
int div_command(Processor& processor);

using COMMANDTYPE = int (*)(Processor& processor);

const int COMMANDSVERSION = 2;