#pragma once

#include "../Processor/Processor.h"
#include "InteractiveCode.h"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode code);
ErrorCode executeCommand(Processor& processor, std::wstring& line, InteractiveCode& code);

ErrorCode defaultPrint(Processor& processor);

