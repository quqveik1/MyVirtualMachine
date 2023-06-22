#pragma once

#include <string>

#include "CompileData.h"
#include "FileListing.h"


using COMMANDLISTINGTYPE = int (*)(FileListing& fileListing, int bytePosBefore, int bytePosAfter);

int addDefaultLineToListing(FileListing& fileListing, int bytePosBefore, int bytePosAfter);