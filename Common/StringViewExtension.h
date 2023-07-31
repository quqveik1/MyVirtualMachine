#pragma once

template <typename T1, typename T2>
int svcmp(const T1& str1, const T2& str2);

template <typename TS>
int strToNum(const TS& str, int radix = 10);

template <typename _CHARACTER>
int charToDigit(_CHARACTER c, int radix = 10);

template <typename T, typename TS>
T strToFloat(const TS& str);

template <typename TS>
void findNumStart(const TS& str, size_t& numberStart, bool& isNegative);