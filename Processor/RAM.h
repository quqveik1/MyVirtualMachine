#pragma once

#include <vector>

#include "../Constants/CommandConstants.h"

struct RAM
{
    const CommandDataType        arrSize   = 100;

    const CommandDataType        xSize;
    const CommandDataType        ySize;
    CommandDataType              VRAMSize;

    CommandDataType              TotalSize;
private:
    std::vector<CommandDataType> data;

public:
                    RAM        (int _xSize, int _ySize);

    CommandDataType& operator[](CommandDataType index);

    void            print      (CommandDataType index);

    CommandDataType getPixel   (CommandDataType x, CommandDataType y);
    void            setPixel   (CommandDataType x, CommandDataType y, CommandDataType pix);
};