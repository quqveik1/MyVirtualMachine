#pragma once
#include "Converter.h"
#include "../CompileCommands.cpp"
#include "../FileHeader.h"
#include "../CompileData.cpp"
#include "../ByteConverter.cpp"

void convertToNum(std::wstring path)
{
    setlocale(LC_ALL, "russian");

    initCompileArr();
    initSizeArr();

    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    CompileData dataArr;
    dataArr.getData().reserve(cLines);

    char** dataLines = new char*[cLines]{};
    int* commandNums = new int[cLines]{};

    int runRes = interpretText(lines, dataArr, cLines);

    if (runRes != WellCode)
    {
        std::cout << "Ошибка перевода в байтовый вид, код: " << runRes << "\n";
    }
    else
    {
        save2Files(lines, dataArr, cLines, path);
    }

    clearMem(fullText, lines, dataArr, cLines);

    std::cout << "Компиляция завершилась успешно\n";
}

//Формат номера команд:
//8765 4321
//00ri ####
//0001 0004
//Новый синтаксис(складывает)
//push ax+10
//push 10+ax

void save2Files(std::wstring_view* oldLines, CompileData& dataArr, int cLines, std::wstring path)
{
    std::wstring savePath = path + L'c';
    std::ofstream file(savePath, std::ios::binary);

    FileHeader fileHeader;

    file.write((char*)&fileHeader, sizeof(FileHeader));

    size_t writeSize = sizeof(char) * dataArr.getData().size();

    file.write(&(dataArr.getData())[0], writeSize);

    file.close();
}

void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, CompileData& dataArr, int cLines)
{
    delete[] oldLines;

    delete[] fullText.data();
}

int interpretText(std::wstring_view* oldLines, CompileData& dataArr, int cLines)
{
    for (int i = 0; i < cLines; i++)
    {
        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        int commandNum = getCommandNum(commandName);

        if (!isCommandNumValid(commandNum))
        {
            std::wcout << L"Ошибка в распозновании команды в строке (" << i << L") [" << commandName << L"]\n";
            std::wcout << L"\"" << oldLines[i] << "\"\n";
            return CommandReadErrorCode;
        }

        int writeNum = codeToNumberRepresentation(commandNum, 0, 0);

        dataArr.put(&commandNum);

        COMMANDCOMPILETYPE fnc = commandsCompileArr[commandNum];

        if (fnc != NULL)
        {
            char* _binaryData = NULL;
            int _dataSize = fnc(commandData, &_binaryData);
            dataArr.put(_binaryData, _dataSize);
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
    if (_wcsnicmp(commandName.data(), in_str.c_str(), commandName.size()) == 0)
    {
        res = in_num;
    }

    else if (_wcsnicmp(commandName.data(), out_str.c_str(), commandName.size()) == 0)
    {
        res = out_num;
    }

    else if (_wcsnicmp(commandName.data(), push_str.c_str(), commandName.size()) == 0)
    {
        res = push_num;
    }

    else if (_wcsnicmp(commandName.data(), hlt_str.c_str(), commandName.size()) == 0)
    {
        res = hlt_num;
    }

    else if (_wcsnicmp(commandName.data(), add_str.c_str(), commandName.size()) == 0)
    {
        res = add_num;
    }

    else if (_wcsnicmp(commandName.data(), sub_str.c_str(), commandName.size()) == 0)
    {
        res = sub_num;
    }

    else if (_wcsnicmp(commandName.data(), mul_str.c_str(), commandName.size()) == 0)
    {
        res = mul_num;
    }

    else if (_wcsnicmp(commandName.data(), div_str.c_str(), commandName.size()) == 0)
    {
        res = div_num;
    }

    return res;
}
