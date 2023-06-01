#pragma once

#include <string>    

#include "..\CompileData.h"

int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, CompileData& dataArr, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, CompileData& dataArr, int cLines);
int interpretText(std::wstring_view* oldLines, CompileData& dataArr, int cLines);
void convertToNum(std::wstring path);