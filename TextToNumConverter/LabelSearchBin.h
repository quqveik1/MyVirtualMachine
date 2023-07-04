#pragma once

#include <map>
#include <string_view>
#include <vector>

struct LabelSearchBin
{
    LabelSearchBin(struct BinCompileData* _compileData);
    ~LabelSearchBin();

private:
    std::map<int, int> words;
    std::map<int, std::vector<int>> fixUpList;

    struct BinCompileData* binCompileData;

public:
    int getWordPos(int wordLine);
    void pushWord(int wordLine, int pos = -1);

    void writeOrWaitLabel(int wordLine, int pos = -1);

private:
    void checkFixUpList(int wordLine, int pos);
};
