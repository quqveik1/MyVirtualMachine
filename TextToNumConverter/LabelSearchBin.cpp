#pragma once

#include "LabelSearchBin.h"

LabelSearchBin::LabelSearchBin(struct BinCompileData* _compileData) :
    binCompileData(_compileData)
{

}

LabelSearchBin::~LabelSearchBin()
{
    if (!fixUpList.empty())
    {
        std::cout << "Words waiting list is not empty\n";
    }
}

int LabelSearchBin::getWordPos(int wordLine)
{
    auto it = words.find(wordLine);

    if (it == words.end())
    {
        return -1;
    }

    return it->second;
}

void LabelSearchBin::pushWord(int wordLine, int pos/* = -1*/)
{
    if (pos < 0)
    {
        pos = binCompileData->getCurrPos();
    }

#ifdef _DEBUG
    auto it = words.find(wordLine);

    if (it != words.end())
    {
        throw std::runtime_error("Try to dublicate word");
    }
#endif

    checkFixUpList(wordLine, pos);

    words[wordLine] = pos;
}


void LabelSearchBin::writeOrWaitLabel(int wordLine, int pos/* = -1*/)
{
    int wordPos = getWordPos(wordLine);
    if (wordPos >= 0)
    {
        int convertedWordPos = convNum(wordPos);
        binCompileData->put(convertedWordPos);
        return;
    }

    if (pos < 0)
    {
        pos = binCompileData->getCurrPos();
    }
    binCompileData->put(wordPos);

    fixUpList[wordLine].push_back(pos);
}

void LabelSearchBin::checkFixUpList(int wordLine, int pos)
{
    auto it = fixUpList.find(wordLine);
    if (it == fixUpList.end())
    {
        return;
    }

    while (!it->second.empty())
    {
        int convertedPos = convNum(pos);
        int insertPos = it->second[it->second.size() - 1];
        binCompileData->change(convertedPos, insertPos);

        it->second.pop_back();
    }

    fixUpList.erase(it);
}