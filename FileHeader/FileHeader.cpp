#pragma once
#include "FileHeader.h"

#include "Encryption.cpp"

bool FileHeader::validate(const char* file, size_t len)
{
    for (int i = 0; i < 4; i++)
    {
        if (sign[i] != ORIGINALSIGN[i])
        {
            return false;
        }
    }

    uint32_t _hashSum = hashArr(file, len);

    if (_hashSum != hashSum) return false;

    return true;
}

void FileHeader::setHashSum(const char* file, size_t len)
{
    hashSum = hashArr(file, len);
}
