//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <queue>
#include <stack>

class RuntimeData
{
    std::queue<std::string> input;
    std::queue<int> appData;

public:
    std::queue<std::string> &getInput();

    std::queue<int> &getAppData();
};

RuntimeData AppRuntimeData;

