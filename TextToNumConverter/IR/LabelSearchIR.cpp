#pragma once

#include "LabelSearchIR.h"

#include "../../Common/StackFunc.cpp"
#include "../../Converter/FloatConvert.cpp"
#include "CommandIR.h"
#include "../../Constants/CommandConstants.h"


LabelSearchIR::LabelSearchIR(IR* _ir) :
    ir(_ir)
{
    
}

LabelSearchIR::~LabelSearchIR()
{
    
}

int LabelSearchIR::getWordPos(std::wstring_view& word)
{
    auto it = words.find(word);

    if (it == words.end())
    {
        return -1;
    }

    return it->second;
}

void LabelSearchIR::pushWord(std::wstring_view& word, int pos/* = -1*/)
{
    if (pos < 0)
    {
        pos = (int)ir->getActiveCommandNum();
    }

#ifdef _DEBUG
    auto it = words.find(word);

    if (it != words.end())
    {
        throw std::runtime_error("Try to dublicate word");
    }
#endif

    checkFixUpList(word, pos);

    words[word] = pos;
}


void LabelSearchIR::writeOrWaitLabel(std::wstring_view& word, CommandIR* commandIR)
{
    int wordPos = getWordPos(word);
    if(wordPos >= 0)
    {
        commandIR->setLabelLinePos(wordPos);
        return;
    }

    fixUpList[word].push_back(commandIR);
}

ErrorCode LabelSearchIR::checkLabelLinking()
{
    if (!fixUpList.empty())
    {
        std::cout << "Label fix up list is not empty\n";
        std::cout << "These words were not linked:\n";      
        for(auto& el : fixUpList)
        {
            std::wcout << el.first << L" | ";

            for(size_t i = 0; i < el.second.size(); i++)
            {
                std::cout << std::setw(5) << std::setfill('0') << el.second[i]->getLinePos();
                if(el.second.size() - i > 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "These words were found in code:\n";
        for (auto& el : words)
        {
            std::wcout << el.first << L"\n";
        }
        return ErrorCode::NotEmptyFixUpLinkingLabelList;
    }

    return ErrorCode::WellCode;
}

void LabelSearchIR::checkFixUpList(std::wstring_view& word, int pos)
{
    auto it = fixUpList.find(word);
    if(it == fixUpList.end())
    {
        return;
    }

    while (!it->second.empty())
    {
        CommandDataType convertedPos = convNum(pos);
        CommandIR* insertCommand = it->second[it->second.size() - 1];
        insertCommand->setLabelLinePos(pos);

        it->second.pop_back();
    }

    fixUpList.erase(it);
}