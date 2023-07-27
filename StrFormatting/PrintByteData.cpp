#pragma once

#include "PrintByteData.h"

const bool needNewLine = true;
const bool noNewLine = false;

template <typename ARR, typename TS>
void printByteData(ARR* data, size_t bytePosBefore, size_t bytePosAfter, TS& originalLine, const int margin, std::wstring& newStr, const int byteDataPrintLen/* = DefaultByteDataPrintLen*/)
{
    size_t cursorPos = bytePosBefore;
    bool isFirstStr = true;

    for (;;)
    {

        if (!isFirstStr)
        {
            for (int i = 0; i < margin; i++)
            {
                newStr += L' ';
            }
        }

        newStr += L" | ";

        bool res = printDataLine(data, cursorPos, bytePosAfter, newStr, byteDataPrintLen);

        if (res == needNewLine)
        {
            newStr += L'+';
            newStr += L" | ";
        }
        else
        {
            newStr += L"  | ";
        }

        if (isFirstStr) newStr += originalLine;

        isFirstStr = false;

        if (res == noNewLine) break;
        else
        {
            newStr += L'\n';
        }
    }
}

template <typename ARR>
bool printDataLine(ARR* buffer, size_t& cursorPos, size_t bytePosAfter, std::wstring& newStr, const int byteDataPrintLen)
{
    size_t startPos = cursorPos;

    wchar_t hexBuff[4]{};

    for (; cursorPos - startPos < byteDataPrintLen; cursorPos++)
    {
        if (cursorPos < bytePosAfter)
        {
            unsigned char printByte1 = (*buffer)[cursorPos];
            swprintf(hexBuff, 4, L"%02x ", printByte1);
            newStr += hexBuff;
        }
        else
        {
            newStr += L"   ";
        }
    }

    bool hasFreeSpace = cursorPos < bytePosAfter;

    return hasFreeSpace;
}