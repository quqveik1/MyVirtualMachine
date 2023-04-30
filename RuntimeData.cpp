//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "RuntimeData.h"

std::queue<std::string> &RuntimeData::getInput()
{
    return input;
}

std::queue<int> &RuntimeData::getAppData()
{
    return appData;
}
