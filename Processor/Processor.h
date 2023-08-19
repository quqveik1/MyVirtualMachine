#pragma once

#include "RuntimeData.cpp"
#include "DataStack.cpp"
#include "Register/Register.cpp"
#include "RAM.cpp"
#include "CallStack.h"
#include "ProcessorDebug\RuntimeInfoCollector.h"
#include "BreakPoint/Breakpoints.h"
#include "Constants/ErrorCode.h"

namespace sf
{
    class RenderWindow;
}

struct Processor
{
    Processor();
    ~Processor();

private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;
    RAM         appRAM;
    CallStack   callStack;

    RuntimeInfoCollector   runtimeInfoCollector;
    Breakpoints            breakpoints;

    const int xSize = 268;
    const int ySize = 201;
    bool isProgrammActive = true;
    sf::RenderWindow* program_window = nullptr;

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
    void endProgramWithCode(ErrorCode code);
    ErrorCode executeCommand();

    void startUiThread();
    void observeFrame(sf::RenderWindow& window);
    void drawFrame   (sf::RenderWindow& window);
    void drawLines   (sf::RenderWindow& window);
    void drawVram    (sf::RenderWindow& window);
};