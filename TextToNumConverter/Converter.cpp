#pragma once
#include "Converter.h"

void convertToNum(std::wstring path)
{
    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    std::wstring_view* dataLines = new std::wstring_view[cLines]{};
    int* commandNums = new int[cLines]{};

    std::vector<int> intByteArr(cLines);

    interpretText(lines, dataLines, commandNums, cLines);

    save2Files(lines, dataLines, commandNums, cLines, path);

    delete fullText.data();
}

void save2Files(std::wstring_view* oldLines, std::wstring_view* dataLines, int* commandNums, int cLines, std::wstring path)
{
    std::wstring savePath = path + L'c';
    std::ofstream file(savePath, std::ios::binary);
    
    for (int i = 0; i < cLines; i++)
    {
        file.write((char*)&commandNums[i], sizeof(int));
        if (!dataLines[i].empty())
        {
            int nums = _wtoi(dataLines[i].data());
            file.write((char*)&nums, sizeof(int));
        }
    }

    file.close();
}

void interpretText(std::wstring_view* oldLines, std::wstring_view* dataLines, int* commandNums, int cLines)
{
    for (int i = 0; i < cLines; i++)
    {
        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        int commandNum = getCommandNum(commandName);
        commandNums[i] = commandNum;
        dataLines[i] = commandData;
    }
}

int writeOneLine(int commandNum, std::wstring_view& commandData, std::wstring& line)
{
    line = std::to_wstring(commandNum) + L" " + std::wstring(commandData);
    return 0;
}

/*
push 10
add
push 10
mul

->

5 10
3
5 10
4

*/

int getCommandNum(std::wstring_view& commandName)
{
    int res = commandError_num;
    if (_wcsnicmp(commandName.data(), in_str, commandName.size()) == 0)
    {
        res = in_num;
    }

    else if (_wcsnicmp(commandName.data(), out_str, commandName.size()) == 0)
    {
        res = out_num;
    }

    else if (_wcsnicmp(commandName.data(), push_str, commandName.size()) == 0)
    {
        res = push_num;
    }

    else if (_wcsnicmp(commandName.data(), hlt_str, commandName.size()) == 0)
    {
        res = hlt_num;
    }

    else if (_wcsnicmp(commandName.data(), add_str, commandName.size()) == 0)
    {
        res = add_num;
    }

    else if (_wcsnicmp(commandName.data(), sub_str, commandName.size()) == 0)
    {
        res = sub_num;
    }

    else if (_wcsnicmp(commandName.data(), mul_str, commandName.size()) == 0)
    {
        res = mul_num;
    }

    else if (_wcsnicmp(commandName.data(), div_str, commandName.size()) == 0)
    {
        res = div_num;
    }

    return res;
}
