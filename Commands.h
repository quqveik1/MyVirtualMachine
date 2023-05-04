//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include "RuntimeData.h"

#define RuntimeAppData RuntimeData

int in_command(RuntimeAppData& appData, std::string_view commandData);
int out_command(RuntimeAppData& appData, std::string_view commandData);