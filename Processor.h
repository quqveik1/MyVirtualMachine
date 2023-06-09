#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register.cpp"
#include "RAM.cpp"
#include "CallStack.h"

struct Processor
{
    Processor();

private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;
    RAM         appRAM;
    CallStack   callStack;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
    RAM&         getAppRAM()      { return appRAM; };
    CallStack&   getCallStack()   { return callStack; };
};