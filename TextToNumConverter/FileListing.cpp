#pragma once

#include "FileListing.h"

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
    return default_listing(commandIR.getData(), 0, commandIR.getData().size());
}

const bool needNewLine = true;
const bool noNewLine = false;

int FileListing::default_listing(std::vector<char>& data, size_t bytePosBefore, size_t bytePosAfter)
{
    addNewListingLine();

    wchar_t buffer[15]{};
    swprintf(buffer, 15, L"%03d: %05x", getActiveOriginalCodeLineNum(), (int)bytePosBefore);

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

        if (isFirstStr) listingFile += getActiveOriginaFileLine();

        isFirstStr = false;

        if (res == noNewLine) break;
        else
        {
            addNewListingLine();
        }
    }

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

std::wstring_view& FileListing::getActiveOriginaFileLine()
{
    return getOriginalFileLines()[getActiveOriginalCodeLineNum()];
};

void FileListing::saveInFile(std::wstring path)
{
    std::ofstream listing(path);
    saveText(getFileListing(), (int)getFileListing().size(), listing, false);
}