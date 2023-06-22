#pragma once

#include "ListCommands.h"

#include "../CommandConstants.h"

const bool needNewLine = true;
const bool noNewLine = false;

int default_listing(FileListing& fileListing, int bytePosBefore, int bytePosAfter)
{
    fileListing.addNewListingLine();

    wchar_t buffer[15]{};
    swprintf(buffer, 15, L"%03d: %05x", fileListing.getActiveOriginalCodeLineNum(), bytePosBefore);

    static const int beforeLineSize = (int)wcslen(buffer);

    

    fileListing.getActiveFileListingString() += buffer;
    

    int cursorPos = bytePosBefore;
    bool isFirstStr = true;

    for(;;)
    {
        std::wstring& listingFile = fileListing.getActiveFileListingString();

        if(!isFirstStr)
        {
            for(int i = 0; i < beforeLineSize; i++)
            {
                listingFile += L' ';
            }
        }

        listingFile += L" | ";

        bool res = printDataLine(fileListing, cursorPos, bytePosAfter);

        if(res == needNewLine)
        {
            listingFile += L'+';
            listingFile += L" | ";
        }
        else
        {
            listingFile += L"  | ";
        }

        if(isFirstStr) listingFile += fileListing.getActiveOriginaFileLine();

        isFirstStr = false;

        if(res == noNewLine) break;
        else
        {
            fileListing.addNewListingLine();
        }
    }

    return WellCode;
}

bool printDataLine(FileListing& fileListing, int& cursorPos, int bytePosAfter)
{
    int startPos = cursorPos;

    wchar_t hexBuff[4]{};

    for(; cursorPos - startPos < ByteDataPrintLen; cursorPos++)
    {
        if (cursorPos < bytePosAfter)
        {
            unsigned char printByte1 = fileListing.getCompileData().getData()[cursorPos];
            swprintf(hexBuff, 4, L"%02x ", printByte1);
            fileListing.getActiveFileListingString() += hexBuff;
        }
        else
        {
            fileListing.getActiveFileListingString() += L"   ";
        }
    }

    bool hasFreeSpace = cursorPos < bytePosAfter;

    return hasFreeSpace;
}

int db_listing(FileListing& fileListing, int bytePosBefore, int bytePosAfter)
{
    int startOfStr = bytePosBefore + sizeof(int) * 2;

    default_listing(fileListing, bytePosBefore, startOfStr);
    return default_listing(fileListing, startOfStr, bytePosAfter);
}