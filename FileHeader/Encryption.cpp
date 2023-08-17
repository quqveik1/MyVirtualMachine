#pragma once

#include "Encryption.h"

uint32_t hashArr(const char* s, size_t len)
{
    uint32_t h = 5381;

    for (size_t i = 0; i < len; i++)
    {
        h = h * 33 + s[i];
    }

    return h;
}