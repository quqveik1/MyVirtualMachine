#pragma once

#include "../Commands.h"
#include "Encryption.h"

const char ORIGINALSIGN[] = { 'K', 'S', 'H', 'I' };

struct FileHeader
{
    char sign[4] = {};
    int version = COMMANDSVERSION;
    uint32_t hashSum = 0;

    FileHeader()
    {
        memcpy(sign, ORIGINALSIGN, 4);
    }

    bool validate(const char* file, size_t len);
    void setHashSum(const char* file, size_t len);
};