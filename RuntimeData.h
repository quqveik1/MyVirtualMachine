//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <stack>

#include "StackVector.h"

struct RuntimeData : StackVector
{
public:
    std::vector<int> &getAppData();

    void printStack(bool needToConvertToUserRepresentation = true);
};

