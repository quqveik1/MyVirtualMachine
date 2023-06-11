#pragma once

#include <string>    

#include "CompileData.h"

int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listringFile, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, std::wstring* listingFile);
void addLineToListing(std::wstring& listingFile, std::wstring_view& oldFile, CompileData& data, int lineNumber);
int interpretText(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listingFile, int cLines);
void convertToNum(std::wstring path);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);    
int findFirstSpacePos(std::wstring_view& fullCommand);