#pragma once

#include "ListCommands.h"

#include "../CommandConstants.h"

int addDefaultLineToListing(FileListing& fileListing, int bytePosBefore, int bytePosAfter)
{
    fileListing.addNewListingLine();

    wchar_t buffer[15]{};
    swprintf(buffer, 15, L"%03d: %05x", fileListing.getListingFileActiveStringIndex(), bytePosBefore);

    std::wstring& listingFile = fileListing.getActiveFileListingString();

    listingFile += buffer;
    listingFile += L" | ";

    int commandLen = bytePosAfter - bytePosBefore;

    int printLen = std::max(ByteDataPrintLen, commandLen);

    for (int i = 0; i < printLen; i++)
    {
        wchar_t hexBuff[4]{};

        if (i < commandLen)
        {
            byte printByte1 = fileListing.getCompileData().getData()[(size_t)bytePosBefore + i];
            swprintf(hexBuff, 4, L"%02x ", printByte1);
            listingFile += hexBuff;
        }
        else
        {
            listingFile += L"   ";
        }
    }

    listingFile += L" | ";

    listingFile += fileListing.getOriginaFileLine();

    return WellCode;
}