#pragma once

#include <string>    

#include "CompileData.h"
#include "FileListing.h"

void save2Files(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listringFile, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, std::wstring* listingFile);
int interpretText(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listingFile, int cLines);
void convertToNum(std::wstring path);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);
void splitCommand(std::wstring_view& fullCommand, int& commandStartPos, int& commandNameLastSym, int& dataFirstSymbol);
int findFirstNotEmptySymPos(std::wstring_view& fullCommand, int startPos = 0);
int findFirstSpacePosAfterCommand(std::wstring_view& fullCommand);