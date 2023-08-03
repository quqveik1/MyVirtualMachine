#pragma once

#include "../Processor/Processor.h"
#include "InteractiveCode.h"

ErrorCode startInteractiveMode(Processor& processor, ErrorCode errorCode, InteractiveCode& code);
ErrorCode executeCommand(Processor& processor, std::wstring_view& line, InteractiveCode& code);

ErrorCode defaultPrint(Processor& processor);

