//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <stack>

#include "StackFunc.h"

class RuntimeData
{
    std::stack<int> appData;

public:
    std::stack<int> &getAppData();

    int peek();
    int get();
    void push(int obj);
};

