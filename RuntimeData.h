//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <queue>
#include <stack>

class RuntimeData
{
    std::stack<std::string> input;
    std::stack<int> appData;

public:
    std::stack<std::string> &getInput();

    std::stack<int> &getAppData();
};

RuntimeData AppRuntimeData;

