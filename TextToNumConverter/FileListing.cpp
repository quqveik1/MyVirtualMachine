#pragma once

#include "FileListing.h"

FileListing::FileListing(BinCompileData& _data, std::wstring_view* _originalFileLines, int cLines, IR& _ir) :
    bincompileData(_data),
    ir(_ir)
{
    fileListing.reserve((int)(cLines*2 + 10));
    initListing();
}

void FileListing::end1Part()
{
    addNewListingLine();
    std::wstring& activeLine = getActiveFileListingString();
    activeLine = L"\n\nFile listing Pass #2: Intermediate Representation -> Machine Code\n\n";

    outputLineNum = 0;
}

void FileListing::initListing()
{
    addNewListingLine();
    std::wstring& activeLine = getActiveFileListingString();
    activeLine = L"File listing Pass #1: Code -> Intermediate Representation\n\n";
}

int FileListing::getListingFileActiveStringIndex()
{
    return (int)getFileListing().size() - 1;
}

std::wstring& FileListing::getActiveFileListingString()
{
    return getFileListing()[getListingFileActiveStringIndex()];
};

void FileListing::addNewListingLine()
{
    getFileListing().resize(getFileListing().size() + 1);
}

int FileListing::add1CompileCommand(CommandIR& commandIR)
{
    return default_listing(commandIR.getData(), 0, commandIR.getData().size(), *commandIR.getLine());
}

int FileListing::add2CompileCommand(CommandIR& commandIR, int bytePosBefore, int bytePosAfter)
{
    return default_listing(getBinCompileData().getData(), bytePosBefore, bytePosAfter, *commandIR.getLine());
}

const bool needNewLine = true;
const bool noNewLine = false;

int FileListing::default_listing(std::vector<char>& data, size_t bytePosBefore, size_t bytePosAfter, std::wstring_view& originalLine)
{
    addNewListingLine();

    wchar_t buffer[15]{};
    swprintf(buffer, 15, L"%03d: %05x", getOutputLineNum(), (int)bytePosBefore);

    static const int beforeLineSize = (int)wcslen(buffer);

    getActiveFileListingString() += buffer;

    size_t cursorPos = bytePosBefore;
    bool isFirstStr = true;

    for (;;)
    {
        std::wstring& listingFile = getActiveFileListingString();

        if (!isFirstStr)
        {
            for (int i = 0; i < beforeLineSize; i++)
            {
                listingFile += L' ';
            }
        }

        listingFile += L" | ";

        bool res = printDataLine(data, cursorPos, bytePosAfter);

        if (res == needNewLine)
        {
            listingFile += L'+';
            listingFile += L" | ";
        }
        else
        {
            listingFile += L"  | ";
        }

        if (isFirstStr) listingFile += originalLine;

        isFirstStr = false;

        if (res == noNewLine) break;
        else
        {
            addNewListingLine();
        }
    }

    outputLineNum++;

    return WellCode;
}

bool FileListing::printDataLine(std::vector<char>& buffer, size_t& cursorPos, size_t bytePosAfter)
{
    size_t startPos = cursorPos;

    wchar_t hexBuff[4]{};

    for (; cursorPos - startPos < ByteDataPrintLen; cursorPos++)
    {
        if (cursorPos < bytePosAfter)
        {
            unsigned char printByte1 = buffer[cursorPos];
            swprintf(hexBuff, 4, L"%02x ", printByte1);
            getActiveFileListingString() += hexBuff;
        }
        else
        {
            getActiveFileListingString() += L"   ";
        }
    }

    bool hasFreeSpace = cursorPos < bytePosAfter;

    return hasFreeSpace;
}

void FileListing::saveInFile(std::wstring path)
{
    std::ofstream listing(path);
    saveText(getFileListing(), (int)getFileListing().size(), listing, false);
}