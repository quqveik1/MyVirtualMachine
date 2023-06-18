#pragma once

#include "FileListing.h"

void addLineToListing(std::wstring& listingFile, std::wstring_view& oldFile, CompileData& data, int lineNumber, int bytePosBefore, int bytePosAfter)
{
    wchar_t buffer[15]{};
    swprintf(buffer, 15, L"%03d: %05x", lineNumber, bytePosBefore);

    listingFile += buffer;
    listingFile += L" | ";

    int commandLen = bytePosAfter - bytePosBefore;

    for (int i = 0; i < ByteDataPrintLen; i++)
    {
        wchar_t hexBuff[4]{};

        if (i < commandLen)
        {
            byte printByte1 = data.getData()[(size_t)bytePosBefore + i];
            swprintf(hexBuff, 4, L"%02x ", printByte1);
            listingFile += hexBuff;
        }
        else
        {
            listingFile += L"   ";
        }
    }

    listingFile += L" | ";

    listingFile += oldFile;
}