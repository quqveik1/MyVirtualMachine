#pragma once

#include <string>

#include "CompileData.h"
#include "FileListing.h"


using COMMANDLISTINGTYPE = int (*)(FileListing& fileListing, int bytePosBefore, int bytePosAfter);

bool printDataLine(FileListing& fileListing, int& cursorPos, int bytePosAfter);
int default_listing(FileListing& fileListing, int bytePosBefore, int bytePosAfter);

int db_listing(FileListing& fileListing, int bytePosBefore, int bytePosAfter);