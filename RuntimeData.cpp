//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "RuntimeData.h"
#include "Stack.cpp"

std::stack<int> &RuntimeData::getAppData()
{
    return getData();
}
