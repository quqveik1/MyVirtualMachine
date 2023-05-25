#pragma once

#include <string>

int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines, std::wstring path);
void clearMem(std::wstring_view& fullText, char** dataLines, int* commandNums, int cLines);
int interpretText(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines);
void convertToNum(std::wstring path);