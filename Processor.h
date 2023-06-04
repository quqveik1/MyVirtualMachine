#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register.cpp"
#include "RAM.cpp"

struct Processor
{
private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;
    RAM         appRAM;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
    RAM&         getAppRAM() { return appRAM; };
};