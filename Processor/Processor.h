#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register/Register.cpp"
#include "RAM.cpp"
#include "CallStack.h"
#include "ProcessorDebug\RuntimeInfoCollector.h"

struct Processor
{
    Processor();

private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;
    RAM         appRAM;
    CallStack   callStack;

    RuntimeInfoCollector   runtimeInfoCollector;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
    RAM&         getAppRAM()      { return appRAM; };
    CallStack&   getCallStack()   { return callStack; };

    RuntimeInfoCollector&   getRuntimeInfoCollector()   { return runtimeInfoCollector; };
};