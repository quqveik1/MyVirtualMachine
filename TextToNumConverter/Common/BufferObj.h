#pragma once


struct BufferObj
{
protected:
    int currPos = 0;
    std::vector<char> data;

public:
    std::vector<char>& getData() { return data; };

    void put(const char* obj, int _size);
    template<typename T>
    void put(T* obj);
    template<typename T>
    void put(T& obj);

    template<typename T>
    void putString(const T& str);

    void change(const char* obj, int _size, int pos);
    template<typename T>
    void change(T& obj, int pos);

    int getCurrPos() { return currPos; }

};