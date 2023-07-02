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

    int outputLineNum = 0;

public:

    FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir);

    void end1Part();

    std::vector<std::wstring>& getFileListing() { return fileListing; };
    BinCompileData& getBinCompileData() { return bincompileData; };
    IR& getIR() { return ir; };

    int getOutputLineNum() { return outputLineNum; }

    int getListingFileActiveStringIndex();
    std::wstring& getActiveFileListingString();

    void addNewListingLine();

    void saveInFile(std::wstring path);

    int add1CompileCommand(CommandIR& commandIR);
    int add2CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, int bytePosBefore, int bytePosAfter);

private:
    bool printDataLine(std::vector<char>& buffer, size_t& cursorPos, size_t bytePosAfter);
    void printByteData(std::vector<char>& data, size_t bytePosBefore, size_t bytePosAfter, std::wstring_view& originalLine, const int margin);
    void initListing();
};
