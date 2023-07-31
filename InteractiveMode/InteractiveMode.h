#pragma once

#include "../Processor/Processor.h"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode code);


ErrorCode defaultPrint(Processor& processor);

void printRuntimeData(Processor& processor);
void printRuntimeInfoDissassembler(Processor& processor);
void printCallStack(Processor& processor);
void printRegisters(Processor& processor);