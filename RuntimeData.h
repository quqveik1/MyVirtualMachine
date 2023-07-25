//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <stack>

#include "StackFunc.h"
#include "Stack.h"

struct RuntimeData : Stack
{
public:
    std::stack<int> &getAppData();

    void printStack();
};

