#pragma once

int codeToNumberRepresentation(int num, bool hasConstant, bool hasRegister);
int decodeNumberRepresentation(int codeNum, bool* hasConstant, bool* hasRegister);

int codeToDataRepr(int data, bool isRegister);
int decodeDataRepr(int data, bool* isRegister);