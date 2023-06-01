//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <queue>
#include <stack>

class RuntimeData
{
    std::stack<int> appData;

public:
    std::stack<int> &getAppData();
};

