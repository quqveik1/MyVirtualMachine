#pragma once

struct RAM
{
    const CommandDataType arrSize          = 100;
    static const CommandDataType TotalSize = 10100;

    const CommandDataType xSize            = 100;
    const CommandDataType ySize            = 100;
    const CommandDataType VRAMSize         = 10000;
private:
    CommandDataType data[TotalSize]{};

public:
    CommandDataType& operator[](CommandDataType index);

    void print     (CommandDataType index);

    CommandDataType getPixel   (CommandDataType x, CommandDataType y);
    void setPixel  (CommandDataType x, CommandDataType y, CommandDataType pix);
};