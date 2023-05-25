#pragma once

#include "Commands.h"

const char ORIGINALSIGN[] = { 'K', 'S', 'H', 'I' };

struct FileHeader
{
    char sign[4] = {};
    int version = COMMANDSVERSION;

    FileHeader()
    {
        for (int i = 0; i < 4; i++)
        {
            sign[i] = ORIGINALSIGN[i];
        }
    }

    bool validate();
};