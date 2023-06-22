#pragma once

#include <string>
#include <string_view>

#include "CompileData.h"

const int ByteDataPrintLen = 16;

struct FileListing
{
private:
    std::vector<std::wstring> fileListing;
    CompileData& compileData;
    std::wstring_view* originalFileLines;

    int activeOriginalCodeLineNum;

public:

    FileListing(CompileData& _data, std::wstring_view* _originalFileLines, int cLines) :
        compileData(_data),
        originalFileLines(_originalFileLines),
        activeOriginalCodeLineNum(0)
    {
        fileListing.reserve((int)cLines);
    }

    std::vector<std::wstring>& getFileListing() { return fileListing; };
    CompileData& getCompileData() { return compileData; };
    std::wstring_view* getOriginalFileLines() { return originalFileLines; };

    void setActiveOriginalCodeLineNum(int line) { activeOriginalCodeLineNum = line; }
    int getActiveOriginalCodeLineNum() { return activeOriginalCodeLineNum; }

    std::wstring_view& getActiveOriginaFileLine();

    int getListingFileActiveStringIndex();
    std::wstring& getActiveFileListingString();

    void addNewListingLine();

    void saveInFile(std::wstring path);
};
