#pragma once

#include <vector>

struct CompileData
{
private:
    int currPos = 0;
    std::vector<char> data;
public:
    std::vector<char>& getData() { return data; };

    void put(const char* obj, int _size);
    template<typename T>
    void put(T* obj);
};