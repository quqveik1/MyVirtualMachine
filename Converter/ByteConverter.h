#pragma once

#include "../Constants/CommandConstants.h"

CommandType codeToNumberRepresentation(CommandType num,     bool hasConstant = false, bool hasRegister = false, bool isRamCall = false);
CommandType decodeNumberRepresentation(CommandType codeNum, bool* hasConstant = NULL, bool* hasRegister = NULL, bool* isRamCall = NULL);