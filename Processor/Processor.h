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
    Processor(int screenX, int screenY, bool _needGraphicsWindow);
    ~Processor();

private:
    RuntimeData runtimeData;
    DataStack   commandData;
    Register    appRegister;
    RAM         appRAM;
    CallStack   callStack;

    RuntimeInfoCollector   runtimeInfoCollector;
    Breakpoints            breakpoints;

    const int xSize;
    const int ySize;
    bool isProgrammActive = true;
    sf::RenderWindow* program_window = nullptr;
    bool needGraphicsWindow = false;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack&   getCommandData() { return commandData; };
    Register&    getAppRegister() { return appRegister; };
    RAM&         getAppRAM     () { return appRAM; };
    CallStack&   getCallStack  () { return callStack; };

    RuntimeInfoCollector&   getRuntimeInfoCollector()   { return runtimeInfoCollector; };
    Breakpoints&            getBreakpoints         ()   { return breakpoints; };

    ErrorCode startExecutingProgramm(std::string& path);
    ErrorCode readFile              (std::string& path);

private:

    void readAndExecuteCommands();
    void endProgramWithCode    (ErrorCode code);
    ErrorCode executeCommand   ();

    void      startUiThread();
    ErrorCode startUiJob   ();
    void observeFrame (sf::RenderWindow& window);
    void drawFrame    (sf::RenderWindow& window);
    void drawLines    (sf::RenderWindow& window);
    void drawVram     (sf::RenderWindow& window);
};