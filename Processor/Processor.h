#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register/Register.cpp"
#include "RAM.cpp"
#include "CallStack.h"
#include "ProcessorDebug\RuntimeInfoCollector.h"
#include "BreakPoint/Breakpoints.h"
#include "Constants/ErrorCode.h"

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
    Breakpoints   breakpoints;

    const int xSize = 800;
    const int ySize = 800;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
    RAM&         getAppRAM()      { return appRAM; };
    CallStack&   getCallStack()   { return callStack; };

    RuntimeInfoCollector&   getRuntimeInfoCollector()   { return runtimeInfoCollector; };
    Breakpoints&            getBreakpoints()   { return breakpoints; };

    ErrorCode startExecutingProgramm(std::string& path);
    ErrorCode readFile(std::string& path);

private:

    void readAndExecuteCommands();
    void endProgramWithCode(int code);
    int executeCommand();

    void startUiThread();
};