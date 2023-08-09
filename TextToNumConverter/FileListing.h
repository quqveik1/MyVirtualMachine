#pragma once

#include <string>
#include <string_view>

#include "Bin/BinCompileData.h"
#include "IR/IR.h"

struct FileListing
{
private:
    std::wstring fileListing;
    BinCompileData& bincompileData;
    IR& ir;

    int outputLineNum = 0;

public:

    FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir);

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

    int add1CompileCommand(CommandIR& commandIR);
    int add2CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    int add3CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter);
    int add2PartCommand   (CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter, int passNum);

private:
    void initListing();
};