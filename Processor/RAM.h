#pragma once

struct RAM
{
    static const int arrSize = 100;
private:
    int data[arrSize]{};

public:
    int& operator[](int index);

    void print(int index);
};