#pragma once

#include <vector>
#include <string>
#include <string_view>

const int DefaultByteDataPrintLen = 16;

template <typename ARR, typename TS>
void printByteData(ARR* data, size_t bytePosBefore, size_t bytePosAfter, TS& originalLine, const int margin, std::wstring& newStr, const int defaultByteDataPrintLen = DefaultByteDataPrintLen);

template <typename ARR>
bool printDataLine(ARR* buffer, size_t& cursorPos, size_t bytePosAfter, std::wstring& newStr, const int byteDataPrintLen);