#pragma once

#include <locale>

#include "Converter.h"
#include "CompileCommands.cpp"
#include "../FileHeader.h"
#include "CompileData.cpp"
#include "../ByteConverter.cpp"
#include "../FncArrs.cpp"
#include "WStringFnc.cpp"
#include "../CommandConstants.cpp"

void convertToNum(std::wstring path)
{
    setlocale(LC_ALL, "russian");

    initCompileArr();

    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    CompileData dataArr;
    dataArr.getData().reserve(cLines);

    int runRes = interpretText(lines, dataArr, cLines);

    if (runRes != WellCode)
    {
        std::cout << "Ошибка перевода в байтовый вид, код: " << runRes << "\n";
    }
    else
    {
        save2Files(lines, dataArr, cLines, path);
    }

    clearMem(fullText, lines);

    std::cout << "Компиляция завершилась успешно\n";
}

//Формат номера команд:
//8765 4321
//0mri ####
//0001 1001
//Новый синтаксис(складывает)
//push ax+10
//push 10+ax

/*
    индекс в массиве машинного кода
jmp 5

jamp above вызывается если первое число больше второго
push 7
push 5
ja 5
jae 5
jb 
jbe 
je 
jne 
*/

/*
push [25]
pop [ax]
*/

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

void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines)
{
    if(oldLines)         delete[] oldLines;

    if (fullText.data()) delete[] fullText.data();
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

        COMMANDCOMPILETYPE fnc = commandsCompileArr[commandNum];

        if (fnc != NULL)
        {
            int res = fnc(dataArr, commandNum, commandData);
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



void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData)
{
    int spacePos = findFirstSpacePos(fullCommand);
    commandName = fullCommand.substr(0, spacePos);
    if (spacePos >= 0)
    {
        commandData = fullCommand.substr((size_t)spacePos + 1);
    }
}

int findFirstSpacePos(std::wstring_view& fullCommand)
{
    for (int i = 0; i < (int)fullCommand.size(); i++)
    {
        if (fullCommand[i] == ' ')
        {
            return i;
        }
    }
    return -1;
}
