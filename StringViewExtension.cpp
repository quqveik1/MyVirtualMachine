#pragma once

#include "StringViewExtension.h"

#include <algorithm>
#include <cctype>

template <typename T1, typename T2>
int svcmp(const T1& str1, const T2& str2)
{
    if(str1.size() != str2.size())
    {
        if(str1.size() > str2.size())
        {
            return (int)(str1.size() - str2.size());
        }     
        else
        {
            int res = (int)(str2.size() - str1.size());

            return -res;
        }
    }

    for(size_t i = 0; i < str1.size(); i++)
    {
        if(str1[i] != str2[i])
        {
            int res = (int)(i + 1);
            return res;
        }
    }

    return 0;
}

template <typename TS>
int strToNum(const TS& str, int radix/* = 10*/)
{
    int number = 0;
    bool isNegative = false;
    size_t i = 0;

    findNumStart(str, i, isNegative);

    for (;;)
    {
        if (i < str.size())
        {
            if(isspace(str[i]))
            {
                break;
            }
            else
            {
                number = number * radix + charToDigit(str[i], radix);
                i++;
            }
        }
        else
        {
            break;
        }
    }

    if (isNegative) number *= -1;

    return number;
}

template <typename _CHARACTER>
int charToDigit(_CHARACTER c, int radix/* = 10*/)
{
    int ans = 0;

    if (isdigit(c))
    {
        ans = c - '0';
    }
    else
    {
        if (radix > 10)
        {
            c = tolower(c);
        }
        ans = (c - 'a') + 10;
    }

    if(ans >= radix)
    {
        throw std::exception("c > radix");
    }

    if (ans < 0)
    {
        throw std::runtime_error("c isn't num");
    }

    return ans;
}

template <typename T, typename TS>
T strToFloat(const TS& str)
{
    T result = 0;
    T factor = 1;

    bool decimalPointEncountered = false;

    size_t i = 0;
    bool isNegative = false;

    findNumStart(str, i, isNegative);

    for (;; i++)
    {
        if(i >= str.size())
        {
            break;
        }

        if (isdigit(str[i]))
        {
            if (decimalPointEncountered)
            {
                factor /= 10;
                result += charToDigit(str[i]) * factor;
            }
            else
            {
                result = result * 10 + charToDigit(str[i]);
            }
        }
        else if (str[i] == '.')
        {
            if (decimalPointEncountered)
            {
                throw std::exception("Invalid format: Multiple decimal points.");
            }
            decimalPointEncountered = true;
        }
        else if (isspace(str[i]))
        {
            break;
        }
        else
        {
            throw std::exception("Invalid character encountered.");
        }
    }

    if (isNegative) result *= -1;

    return result;
};


template <typename TS>
void findNumStart(const TS& str, size_t& numberStart, bool& isNegative)
{
    size_t i = 0;
    for (;; i++)
    {
        if (i < str.size())
        {
            if (!isspace(str[i]))
            {
                break;
            }
        }
        else
        {
            throw std::exception("empty str");
        }
    }

    if (str[i] == '-')
    {
        isNegative = true;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
        isNegative = false;
    }

    for (;; i++)
    {
        if (i < str.size())
        {
            if (!isspace(str[i]))
            {
                break;
            }
        }
        else
        {
            throw std::exception("empty str");
        }
    }

    numberStart = i;
}