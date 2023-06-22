#pragma once

#include <string>

#include "CompileData.h"

const int ByteDataPrintLen = 20;

struct FileListing
{
private:
    std::vector<std::wstring> fileListing;
    CompileData& compileData;
    std::wstring_view* originalFileLines;

    int originalCodeLine;

public:

    FileListing(CompileData& _data, std::wstring_view* _originalFileLines, int cLines) :
        compileData(_data),
        originalFileLines(_originalFileLines),
        originalCodeLine(0)
    {
        fileListing.reserve((int)cLines);
    }

    std::vector<std::wstring>& getFileListing() { return fileListing; };
    CompileData& getCompileData() { return compileData; };
    std::wstring_view* getOriginalFileLines() { return originalFileLines; };

    std::wstring_view& getOriginaFileLine() { return getOriginalFileLines()[originalCodeLine]; };

    int getListingFileActiveStringIndex() { return (int)getFileListing().size() - 1; }

    std::wstring& getActiveFileListingString() { return getFileListing()[getListingFileActiveStringIndex()]; };

    void setOriginalCodeLine(int line) { originalCodeLine = line; }

    void addNewListingLine() { getFileListing().resize(getFileListing().size() + 1); };
};
