#pragma once
#include "Converter.h"
#include "../CompileCommands.cpp"

void convertToNum(std::wstring path)
{
    setlocale(LC_ALL, "russian");

    initCompileArr();
    initSizeArr();

    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    std::vector<int> dataArr(cLines * 2, 0);

    char** dataLines = new char*[cLines]{};
    int* commandNums = new int[cLines]{};

    int runRes = interpretText(lines, dataLines, commandNums, cLines);

    if (runRes != WellCode)
    {
        std::wcout << L"Ошибка перевода в байтовый вид, код: " << runRes << L"\n";
    }
    else
    {
        save2Files(lines, dataLines, commandNums, cLines, path);
    }

    clearMem(fullText, dataLines, commandNums, cLines); 
}

void save2Files(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines, std::wstring path)
{
    std::wstring savePath = path + L'c';
    std::ofstream file(savePath, std::ios::binary);
    
    for (int i = 0; i < cLines; i++)
    {
        file.write((char*)&commandNums[i], sizeof(int));
        if (dataLines[i])
        {
            file.write(dataLines[i], commandDataSizeArr[commandNums[i]]);
        }
    }

    file.close();
}

void clearMem(std::wstring_view& fullText, char** dataLines, int* commandNums, int cLines)
{
    delete fullText.data();

    for (int i = 0; i < cLines; i++)
    {
        delete dataLines[i];
    }

    delete[] dataLines;

    delete[] commandNums;
}

int interpretText(std::wstring_view* oldLines, char** dataLines, int* commandNums, int cLines)
{
    for (int i = 0; i < cLines; i++)
    {
        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        int commandNum = getCommandNum(commandName);
        commandNums[i] = commandNum;

        if (!isCommandNumValid(commandNum))
        {
            std::wcout << L"Ошибка в распозновании команды в строке (" << i << L") [" << commandName << L"]\n";
            std::wcout << L"\"" << oldLines[i] << "\"\n";
            return CommandReadErrorCode;
        }

        COMMANDCOMPILETYPE fnc = commandsCompileArr[commandNum];

        if (fnc != NULL)
        {
            dataLines[i] = fnc(commandData);
        }
    }
    return WellCode;
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
