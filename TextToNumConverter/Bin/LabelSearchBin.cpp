#pragma once

#include "LabelSearchBin.h"

LabelSearchBin::LabelSearchBin(struct BinCompileData* _compileData) :
    binCompileData(_compileData)
{

}

LabelSearchBin::~LabelSearchBin()
{
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

ErrorCode LabelSearchBin::checkLabelLinking()
{
    if (!fixUpList.empty())
    {
        std::cout << "Label fix up list is not empty\n";
        return ErrorCode::NotEmptyFixUpLinkingLabelList;
    }

    return ErrorCode::WellCode;
}


void LabelSearchBin::writeOrWaitLabel(int wordLine, int pos/* = -1*/)
{
    CommandDataType wordPos = getWordPos(wordLine);
    if (wordPos >= 0)
    {
        CommandDataType convertedWordPos = convNum(wordPos);
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
        CommandDataType convertedPos = convNum(pos);
        int insertPos = it->second[it->second.size() - 1];
        binCompileData->change(convertedPos, insertPos);

        it->second.pop_back();
    }

    fixUpList.erase(it);
}