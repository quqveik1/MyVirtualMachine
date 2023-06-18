#pragma once

#include <string>

#include "Comp

void addLineToListing(std::wstring& listingFile, std::wstring_view& oldFile, CompileData& data, int lineNumber, int bytePosBefore, int bytePosAfter);
