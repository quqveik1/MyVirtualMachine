#pragma once

#include "FileListing.h"

#include "../StrFormatting/PrintByteData.cpp"

FileListing::FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir, bool _isActive/* = true*/) :
    bincompileData(_data),
    ir(_ir),
    isActive(_isActive)
{
    fileListing.reserve((int)(cLines*2 + 10));
    initListing();
}

void FileListing::end1Part()
{
    addNewListingLine();
    std::wstring& activeLine = getActiveFileListingString();
    activeLine += L"\n\nFile listing Pass #2: Intermediate Representation -> Machine Code\n";

    outputLineNum = 0;
}

void FileListing::end2Part()
{
    addNewListingLine();
    std::wstring& activeLine = getActiveFileListingString();
    activeLine += L"\n\nFile listing Pass #3: Final Machine Code\n";

    outputLineNum = 0;
}

void FileListing::initListing()
{
    addNewListingLine();
    std::wstring& activeLine = getActiveFileListingString();
    activeLine += L"File listing Pass #1: Code -> Intermediate Representation\n";
}

int FileListing::getListingFileActiveStringIndex()
{
    return (int)getFileListing().size() - 1;
}

std::wstring& FileListing::getActiveFileListingString()
{
    return getFileListing();
};

void FileListing::addNewListingLine()
{
    getActiveFileListingString() += L"\n";
}

ErrorCode FileListing::add1CompileCommand(CommandIR& commandIR)
{
    if(!isActive) return ErrorCode::WellCode;

    addNewListingLine();

    wchar_t buffer[20]{};
    swprintf(buffer, 20, L"%04d | #1 | ", getOutputLineNum());

    static const int startLen = (int)getActiveFileListingString().size();

    getActiveFileListingString() += buffer;

    getActiveFileListingString() += commandIR.toString();

    static const int finishLen = (int)getActiveFileListingString().size();

    static const int marginData = finishLen - startLen;

    printByteData(&commandIR.getData(), 0, commandIR.getData().size(), *commandIR.getLine(), marginData, getActiveFileListingString());

    outputLineNum++;

    return ErrorCode::WellCode;
}

ErrorCode FileListing::add2CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter)
{
    if (!isActive) return ErrorCode::WellCode;
    return add2PartCommand(commandIR, binCompileData, bytePosBefore, bytePosAfter, 2);
}

ErrorCode FileListing::add3CompileCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter)
{
    if(!isActive) return ErrorCode::WellCode;
    return add2PartCommand(commandIR, binCompileData, bytePosBefore, bytePosAfter, 3);
}

ErrorCode FileListing::add2PartCommand(CommandIR& commandIR, BinCompileData& binCompileData, size_t bytePosBefore, size_t bytePosAfter, int passNum)
{
    addNewListingLine();

    wchar_t buffer[20]{};
    swprintf(buffer, 20, L"%03d | #%d | %05x", getOutputLineNum(), passNum, (int)bytePosBefore);

    static const int marginData = (int)wcslen(buffer);

    getActiveFileListingString() += buffer;                                                                                        

    printByteData(&binCompileData.getData(), bytePosBefore, bytePosAfter, *commandIR.getLine(), marginData, getActiveFileListingString());

    outputLineNum++;

    return ErrorCode::WellCode;
}

void FileListing::saveInFile(std::string& path)
{
    if (!isActive) return;

    std::ofstream listing(path);
    saveString(getFileListing(), listing);
}


ErrorCode FileListing::createFinalCodeListing()
{
    if (!isActive) return ErrorCode::WellCode;

    for (size_t i = 0; i < ir.getCommands().size(); i++)
    {
        add3CompileCommand(ir.getCommand((int)i), bincompileData, getBinLinesStart()[i], getBinLinesFinish()[i]);
    }

    return ErrorCode::WellCode;
}