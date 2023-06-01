#pragma once
#include "RuntimeData.cpp"
#include "DataStack.cpp"

struct Processor
{
private:
    RuntimeData runtimeData;

    DataStack commandData;

public:
    RuntimeData& getRuntimeData() { return runtimeData; };
    DataStack& getCommandData() { return commandData; };

};