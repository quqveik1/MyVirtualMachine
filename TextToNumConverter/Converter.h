#pragma once

int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines, std::wstring path);
void clearMem(char** dataLines, int* commandNums, int cLines);
int writeOneLine(int commandNum, std::wstring_view& commandData, std::wstring& line);
int interpretText(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines);
void convertToNum(std::wstring path);