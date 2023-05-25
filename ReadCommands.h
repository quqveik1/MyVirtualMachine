//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <exception>


struct DataStack
{
private:
    char* arr{};
    int size = 0;
    int currPos = 0;

public:

    char* peek(int _size)
    {
        int retPos = currPos;
        if (_size == 0) return NULL;
        currPos += _size;
        if (currPos <= size)
        {
            return &arr[retPos];
        }
        else
        {
            throw std::exception("peek: currPos > size");
        }
        return NULL;
    }

    char* get(int _size)
    {
        if (currPos + _size < size)
        {
            return &arr[currPos];
        }
        else
        {
            throw std::exception("peek: currPos > size");
        }
        return NULL;
    }

    int getSize() { return size; }
    int getCurrPos() { return currPos; }
    void setSize(int _size) { size = _size; }
    void setCurrPos(int _pos) { currPos = _pos; }
    void setArr(char* _arr) { arr = _arr; }
    char* getArr() { return arr; }

};

void initCommandsArr();
void initSizeArr();
void readByteCode(std::string path);
long fileSize(FILE* File);
void readAndExecuteCommands(DataStack& data);
int executeCommand(DataStack& data);
int findFirstSpacePos(std::wstring_view& fullCommand);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);

void endProgramWithCode(int code, int lastLine);