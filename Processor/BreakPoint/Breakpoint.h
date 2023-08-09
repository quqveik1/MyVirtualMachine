#pragma once

struct Breakpoint
{
    int  filePos         = 0;
    int  originalCommand = 0;
    bool isInCode        = false;

    bool operator==(int otherFilePos) const
    {
        return filePos == otherFilePos;
    }
};
