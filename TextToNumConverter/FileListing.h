#pragma once

#include <string>
#include <string_view>

#include "Bin/BinCompileData.h"
#include "IR/IR.h"
#include "../Constants/ErrorCode.h"

struct FileListing
{
private:
    std::wstring fileListing;
    BinCompileData& bincompileData;
    IR& ir;

    std::vector<size_t> binLineStart;
    std::vector<size_t> binLineFinish;
    size_t              activeLineNum = 0;

    int outputLineNum = 0;

    bool isActive = true;

public:

    FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir, bool _isActive = true);

    void end1Part();
    void end2Part();

    std::wstring& getFileListing     () { return fileListing; };
    BinCompileData& getBinCompileData() { return bincompileData; };
    IR& getIR                        () { return ir; };

    void addNewBinLineStart               (size_t pos) { if(isActive) binLineStart.push_back(pos); };
    void addNewBinLineFinish              (size_t pos) { if (isActive) binLineFinish.push_back(pos); };
    std::vector<size_t>& getBinLinesStart () { return binLineStart; };
    std::vector<size_t>& getBinLinesFinish() { return binLineFinish; };

    int getOutputLineNum() { return outputLineNum; }

    int getListingFileActiveStringIndex     ();
    std::wstring& getActiveFileListingString();

    void addNewListingLine();

    void saveInFile(std::string& path);

    ErrorCode add1CompileCommand(CommandIR& commandIR);
    ErrorCode add2CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    ErrorCode add3CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    ErrorCode add2PartCommand   (CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter, int passNum);

    ErrorCode createFinalCodeListing();

private:
    void initListing();
};