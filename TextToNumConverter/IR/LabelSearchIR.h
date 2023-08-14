#pragma once

#include <map>
#include <string_view>
#include <vector>

#include "Bin/BinCompileData.h"
#include "IR/IR.h"

struct LabelSearchIR
{
    LabelSearchIR(struct IR* _ir);
    ~LabelSearchIR();

private:
    std::map<std::wstring_view, int> words;
    std::map<std::wstring_view, std::vector<CommandIR*>> fixUpList;

    struct IR* ir;
    
public:
    int getWordPos       (std::wstring_view& word);
    void pushWord        (std::wstring_view& word, int pos = -1);

    void writeOrWaitLabel(std::wstring_view& word, CommandIR* commandIR);

    ErrorCode checkLabelLinking();

private:
    void checkFixUpList  (std::wstring_view& word, int pos);
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