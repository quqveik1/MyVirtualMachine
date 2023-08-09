#pragma once

#include <string>    

#include "Bin/BinCompileData.h"
#include "FileListing.h"
#include "IR/IR.h"

void save2Files         (std::wstring_view* oldLines, BinCompileData& dataArr, FileListing& fileListing, int cLines, std::wstring path);
void clearMem           (std::wstring_view& fullText, std::wstring_view* oldLines);

bool printAndFinish      (int res, std::wstring str, std::wstring_view& fullText, std::wstring_view* lines);
void printLineError      (int errorCode, int lineNum, std::wstring_view& line);
int createIR             (std::wstring_view* oldLines, IR& ir, int cLines, FileListing& fileListing);
int irToBin              (IR& ir, BinCompileData& compileData, FileListing& fileListing);
int addToListingFinalCode(IR& ir, BinCompileData& compileData, FileListing& fileListing);

void convertToNum        (std::wstring path);
bool ifIsWordDoJob       (std::wstring_view& line, BinCompileData& data);
bool isWord              (std::wstring_view& line, std::wstring_view* word = nullptr);