#pragma once

int codeToNumberRepresentation(int num, bool hasConstant = false, bool hasRegister = false, bool isRamCall = false);
int decodeNumberRepresentation(int codeNum, bool* hasConstant = NULL, bool* hasRegister = NULL, bool* isRamCall = NULL);