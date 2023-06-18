#pragma once

#include <string>

#include "CompileData.h"

const int ByteDataPrintLen = 20;

void addLineToListing(std::wstring& listingFile, std::wstring_view& oldFile, CompileData& data, int lineNumber, int bytePosBefore, int bytePosAfter);
