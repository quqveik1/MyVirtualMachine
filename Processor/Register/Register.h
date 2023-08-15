#pragma once

#include "RegisterCompile.h"

#include "../../Constants/CommandConstants.h"

struct Register
{ 
private:
    CommandDataType arr[cRegister] = {};

public:
    CommandDataType getReg(int num);
    void setReg(int num, CommandDataType value);

    void print(bool needToConvertToUserRepresentation = true);
};