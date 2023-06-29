#pragma once

#include <string>    

#include "BinCompileData.h"
#include "FileListing.h"
#include "IR.h"

void save2Files(std::wstring_view* oldLines, BinCompileData& dataArr, FileListing& fileListing, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines);
int createIR(std::wstring_view* oldLines, IR& ir, int cLines, FileListing& fileListing);
void convertToNum(std::wstring path);
bool ifIsWordDoJob(std::wstring_view& line, BinCompileData& data);
bool isWord(std::wstring_view& line, std::wstring_view& word);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);
void splitCommand(std::wstring_view& fullCommand, int& commandStartPos, int& commandNameLastSym, int& dataFirstSymbol);
int findFirstNotEmptySymPos(std::wstring_view& fullCommand, int startPos = 0);
int findFirstSpacePosAfterCommand(std::wstring_view& fullCommand);
int findLastLineSymbol(std::wstring_view& fullCommand);