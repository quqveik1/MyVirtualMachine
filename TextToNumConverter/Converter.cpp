#pragma once
#include "Converter.h"

void convertToNum(std::wstring path)
{
    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    std::wstring* newLines = new std::wstring[cLines]{};
    int* commandNums = new int[cLines]{};

    interpretText(lines, newLines, commandNums, cLines);

    save2Files(lines, newLines, commandNums, cLines, path);

    delete fullText.data();
}

void save2Files(std::wstring_view* oldLines, std::wstring* newLines, int* commandNums, int cLines, std::wstring path)
{
    std::wstring intSavePath = path + L'c';
    std::ofstream file(intSavePath);

    saveText(newLines, cLines, file, false);

    file.close();
}

void interpretText(std::wstring_view* oldLines, std::wstring* newLines, int* commandNums, int cLines)
{
    for (int i = 0; i < cLines; i++)
    {
        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        int commandNum = getCommandNum(commandName);
        writeOneLine(commandNum, commandData, newLines[i]);
        commandNums[i] = commandNum;
    }
}

int writeOneLine(int commandNum, std::wstring_view& commandData, std::wstring& line)
{
    line = std::to_wstring(commandNum) + L" " + std::wstring(commandData);
    return 0;
}

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
