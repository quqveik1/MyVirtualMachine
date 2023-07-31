#pragma once

#include "RegisterCompile.h"

struct Register
{ 
private:
    int arr[cRegister] = {};

public:
    int getReg(int num);
    void setReg(int num, int value);
};