#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register.h"

struct Processor
{

private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
};