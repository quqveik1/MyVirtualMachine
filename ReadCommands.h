//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <exception>


struct DataStack
{
    char* arr{};
    int size = 0;
    int currPos = 0;

    char* peek(int _size)
    {
        int retPos = currPos;
        currPos += _size;
        if (currPos < size)
        {
            return &arr[retPos];
        }
        else
        {
            throw std::exception("peek: currPos > size");
        }
        return NULL;
    }
};

void initCommandsArr();
void readByteCode(std::string path);
long fileSize(FILE* File);
void readAndExecuteCommands(DataStack& data);
int executeCommand(DataStack& data);
int findFirstSpacePos(std::wstring_view& fullCommand);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);

void endProgramWithCode(int code, int lastLine);