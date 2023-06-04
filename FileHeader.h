#pragma once

#include "Commands.h"

const char ORIGINALSIGN[] = { 'K', 'S', 'H', 'I' };

struct FileHeader
{
    char sign[4] = {};
    int version = COMMANDSVERSION;

    FileHeader()
    {
        memcpy(sign, ORIGINALSIGN, 4);
    }

    bool validate();
};