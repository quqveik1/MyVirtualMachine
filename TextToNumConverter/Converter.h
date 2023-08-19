#pragma once

#include <string>    

#include "Bin/BinCompileData.h"
#include "FileListing.h"
#include "IR/IR.h"

void save2Files                (BinCompileData& dataArr, FileListing& fileListing, std::string& path);
void saveBinCompileData        (BinCompileData& dataArr, std::string& path);
void clearMem                  (std::wstring_view& fullText, std::wstring_view* oldLines);

bool printAndFinish            (ErrorCode res, std::wstring str, std::wstring_view& fullText, std::wstring_view* lines);
void printLineError            (ErrorCode errorCode, int lineNum, std::wstring_view& line);
ErrorCode createIR             (std::wstring_view* oldLines, IR& ir, int cLines, FileListing& fileListing);
ErrorCode irToBin              (IR& ir, BinCompileData& compileData, FileListing& fileListing);

void compile(std::string& path, bool needToCreateFileListing = false);
bool ifIsWordDoJob             (std::wstring_view& line, BinCompileData& data);
bool isWord                    (std::wstring_view& line, std::wstring_view* word = nullptr);