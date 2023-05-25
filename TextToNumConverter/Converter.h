#pragma once

#include <string>

int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, std::vector<int>& dataArr, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, std::vector<int>& dataArr, int cLines);
int interpretText(std::wstring_view* oldLines, std::vector<int>& dataArr, int cLines);
void convertToNum(std::wstring path);