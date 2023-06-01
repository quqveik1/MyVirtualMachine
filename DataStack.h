#pragma once

struct DataStack
{
private:
    char* arr{};
    int size = 0;
    int currPos = 0;

public:

    char* peek(int _size); 
    char* get(int _size);
    template<typename T>
    T* peek(); 
    template<typename T>
    T** get();

    int getSize() { return size; }
    int getCurrPos() { return currPos; }
    void setSize(int _size) { size = _size; }
    void setCurrPos(int _pos) { currPos = _pos; }
    void setArr(char* _arr) { arr = _arr; }
    char* getArr() { return arr; }

};