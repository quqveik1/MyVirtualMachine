#pragma once

struct RAM
{
    const int arrSize = 100;
    static const int TotalSize = 10100;

    const int xSize = 100;
    const int ySize = 100;
    const int VRAMSize = 10000;
private:
    int data[TotalSize]{};

public:
    int& operator[](int index);

    void print(int index);

    int getPixel(int x, int y);
    void setPixel(int x, int y, int pix);
};