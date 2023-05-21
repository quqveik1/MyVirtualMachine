#pragma once
int getCommandNum(std::wstring_view& commandName);
void save2Files(std::wstring_view* oldLines, std::wstring_view* dataLines, int* commandNums, int cLines, std::wstring path);
int writeOneLine(int commandNum, std::wstring_view& commandData, std::wstring& line);
void interpretText(std::wstring_view* oldLines, std::wstring_view* dataLines, int* commandNums, int cLines);
void convertToNum(std::wstring path);