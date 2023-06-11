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
    T* get();


    bool moveCursor(int _delta);
    template<typename T>
    bool moveCursor();

    int getSize() { return size; }
    int getCurrPos() { return currPos; }
    void setSize(int _size) { size = _size; }
    bool setCurrPos(int _pos);
    void setArr(char* _arr) { arr = _arr; }
    char* getArr() { return arr; }

};