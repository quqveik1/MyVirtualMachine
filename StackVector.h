#pragma once

#include <vector>

class StackVector
{
    std::vector<int> data;

public:
    std::vector<int>& getData();

    bool isEmpty() { return getData().empty(); };

    int peek();
    int get();
    void push(int obj);
};