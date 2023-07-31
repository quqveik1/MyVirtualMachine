//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <stack>

#include "../Common/StackVector.h"
#include "../Constants/ErrorCode.h"

struct RuntimeData : StackVector
{
public:
    std::vector<int> &getAppData();

    ErrorCode print(bool needToConvertToUserRepresentation = true);
};

