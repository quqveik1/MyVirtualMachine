//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "RuntimeData.h"

std::stack<std::string> &RuntimeData::getInput()
{
    return input;
}

std::stack<int> &RuntimeData::getAppData()
{
    return appData;
}
