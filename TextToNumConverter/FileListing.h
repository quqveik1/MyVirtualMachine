#pragma once

#include <string>
#include <string_view>

#include "BinCompileData.h"
#include "IR.h"

const int ByteDataPrintLen = 16;

struct FileListing
{
private:
    std::vector<std::wstring> fileListing;
    BinCompileData& bincompileData;
    IR& ir;
    std::wstring_view* originalFileLines;

    int activeOriginalCodeLineNum;

public:

    FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir);

    void end1Part();

    std::vector<std::wstring>& getFileListing() { return fileListing; };
    BinCompileData& getBinCompileData() { return bincompileData; };
    IR& getIR() { return ir; };
    std::wstring_view* getOriginalFileLines() { return originalFileLines; };

    void setActiveOriginalCodeLineNum(int line) { activeOriginalCodeLineNum = line; }
    int getActiveOriginalCodeLineNum() { return activeOriginalCodeLineNum; }

    std::wstring_view& getActiveOriginaFileLine();

    int getListingFileActiveStringIndex();
    std::wstring& getActiveFileListingString();

    void addNewListingLine();

    void saveInFile(std::wstring path);

    int add1CompileCommand(CommandIR& commandIR);

private:
    bool printDataLine(std::vector<char>& buffer, size_t& cursorPos, size_t bytePosAfter);
    int default_listing(std::vector<char>& data, size_t bytePosBefore, size_t bytePosAfter);
    void initListing();
};
