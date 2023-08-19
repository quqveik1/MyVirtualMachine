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

    int outputLineNum = 0;

    bool needToBeActive = true;

public:

    FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir, bool _needToBeActive = true);

    void end1Part();
    void end2Part();

    std::wstring& getFileListing     () { return fileListing; };
    BinCompileData& getBinCompileData() { return bincompileData; };
    IR& getIR                        () { return ir; };

    int getOutputLineNum() { return outputLineNum; }

    int getListingFileActiveStringIndex     ();
    std::wstring& getActiveFileListingString();

    void addNewListingLine();

    void saveInFile(std::wstring path);

    ErrorCode add1CompileCommand(CommandIR& commandIR);
    ErrorCode add2CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    ErrorCode add3CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    ErrorCode add2PartCommand   (CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter, int passNum);

private:
    void initListing();
};