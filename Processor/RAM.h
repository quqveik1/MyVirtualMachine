#pragma once

struct RAM
{
    static const CommandDataType arrSize   = 100;

    static const CommandDataType xSize     = 268;
    static const CommandDataType ySize     = 201;
    static const CommandDataType VRAMSize  = xSize * ySize;

    static const CommandDataType TotalSize = VRAMSize + arrSize;
private:
    CommandDataType* data = new CommandDataType[TotalSize]{};

public:
    ~RAM() { delete[] data; }

    CommandDataType& operator[](CommandDataType index);

    void print     (CommandDataType index);

    CommandDataType getPixel   (CommandDataType x, CommandDataType y);
    void setPixel  (CommandDataType x, CommandDataType y, CommandDataType pix);
};