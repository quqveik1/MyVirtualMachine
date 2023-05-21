#pragma once
int getCommandNum(std::wstring_view& commandName);
int writeOneLine(int commandNum, std::wstring_view& commandData, std::wstring& line);
void interpretText(std::wstring_view* oldLines, std::wstring* newLines, int cLines);
void convertToNum(std::wstring path);