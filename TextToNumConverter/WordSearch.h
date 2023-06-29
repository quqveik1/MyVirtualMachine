#pragma once

#include <map>
#include <string_view>
#include <vector>

#include "BinCompileData.h"

struct WordSearch
{
    WordSearch(struct BinCompileData* _compileData);
    ~WordSearch();

private:
    std::map<std::wstring_view, int> words;
    std::map<std::wstring_view, std::vector<int>> waitingList;

    struct BinCompileData* binCompileData;
    
public:
    int getWordPos(std::wstring_view& word);
    void pushWord(std::wstring_view& word, int pos = -1);

    void writeOrWaitWord(std::wstring_view& word, int pos = -1);

private:
    void checkWaitingList(std::wstring_view& word, int pos);
};

/*
jmp a
jmp b
jmp a
a:
...
b:
..
*/

/*
IR
Pass 1
buffer
len
textLine

Pass 2
*/