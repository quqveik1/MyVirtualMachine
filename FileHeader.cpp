#pragma once
#include "FileHeader.h"


bool FileHeader::validate()
{
    for (int i = 0; i < 4; i++)
    {
        if (sign[i] != ORIGINALSIGN[i])
        {
            return false;
        }
    }
    return true;
}
