#pragma once

#include "WordSearch.h"

#include "../StackFunc.cpp"
#include "../FloatConvert.cpp"


WordSearch::WordSearch(CompileData* _compileData) :
    compileData(_compileData)
{
    
}

WordSearch::~WordSearch()
{
    if(!waitingList.empty())
    {
        std::cout << "Words waiting list is not empty\n";
    }
}

int WordSearch::getWordPos(std::wstring_view& word)
{
    auto it = words.find(word);

    if (it == words.end())
    {
        return -1;
    }

    return it->second;
}

void WordSearch::pushWord(std::wstring_view& word, int pos/* = -1*/)
{
    if (pos < 0)
    {
        pos = compileData->getCurrPos();
    }

#ifdef _DEBUG
    auto it = words.find(word);

    if (it != words.end())
    {
        throw std::runtime_error("Try to dublicate word");
    }
#endif

    checkWaitingList(word, pos);

    words[word] = pos;
}


void WordSearch::writeOrWaitWord(std::wstring_view& word, int pos/* = -1*/)
{
    int wordPos = getWordPos(word);
    if(wordPos >= 0)
    {
        int convertedWordPos = convNum(wordPos);
        compileData->put(convertedWordPos);
        return;
    }

    if (pos < 0)
    {
        pos = compileData->getCurrPos();
    }
    compileData->put(wordPos);

    waitingList[word].push_back(pos);
}

void WordSearch::checkWaitingList(std::wstring_view& word, int pos)
{
    auto it = waitingList.find(word);
    if(it == waitingList.end())
    {
        return;
    }

    while (!it->second.empty())
    {
        int convertedPos = convNum(pos);
        int insertPos = it->second[it->second.size() - 1];
        compileData->change(convertedPos, insertPos);

        it->second.pop_back();
    }

    waitingList.erase(it);
}