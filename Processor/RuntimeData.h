//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <stack>

#include "../Common/StackVector.h"
#include "../Constants/ErrorCode.h"
#include "../Constants/CommandConstants.h"

struct RuntimeData : StackVector<CommandDataType>
{
public:
    std::vector<CommandDataType> &getAppData();

    ErrorCode print(bool needToConvertToUserRepresentation = true);
};

