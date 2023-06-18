#pragma once

#include <locale>
#include <cstdio>

#include "Converter.h"
#include "CompileCommands.cpp"
#include "../FileHeader.h"
#include "CompileData.cpp"
#include "../ByteConverter.cpp"
#include "../FncArrs.cpp"
#include "WStringFnc.cpp"
#include "../CommandConstants.cpp"
#include "../ExtensionConverter.cpp"
#include "FileListing.cpp"

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

    std::wstring* listingFile = new std::wstring[cLines]{};

    int runRes = interpretText(lines, dataArr, listingFile, cLines);

    if (runRes != WellCode)
    {
        std::cout << "Ошибка перевода в байтовый вид, код: " << runRes << "\n";
    }
    else
    {
        save2Files(lines, dataArr, listingFile, cLines, path);
    }

    clearMem(fullText, lines, listingFile);

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

/*
out адрес буквы

db abc
<=>
'a'
'b'
'c'
*/

void save2Files(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listringFile, int cLines, std::wstring path)
{
    std::wstring saveBinPath = path;
    changeExtension(saveBinPath, L"bin");

    std::ofstream file(saveBinPath, std::ios::binary);

    FileHeader fileHeader;

    file.write((char*)&fileHeader, sizeof(FileHeader));

    size_t writeSize = sizeof(char) * dataArr.getData().size();

    file.write(&(dataArr.getData())[0], writeSize);

    file.close();

    std::wstring listingPath = path;
    changeExtension(listingPath, L"lst");

    std::ofstream listing(listingPath);
    saveText(listringFile, cLines, listing, false);
}

void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines, std::wstring* listingFile)
{
    if(oldLines)         delete[] oldLines;

    if (fullText.data()) delete[] fullText.data();

    if (listingFile) delete[] listingFile;
}

int interpretText(std::wstring_view* oldLines, CompileData& dataArr, std::wstring* listingFile, int cLines)
{
    for (int i = 0; i < cLines; i++)
    {
        int bytePosBefore = dataArr.getCurrPos();
        int bytePosAfter = bytePosBefore;

        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        if (commandName.size() > 0)
        {

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

        bytePosAfter = dataArr.getCurrPos();

        addLineToListing(listingFile[i], oldLines[i], dataArr, i, bytePosBefore, bytePosAfter);

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
    int commandStart = findFirstNotEmptySymPos(fullCommand);
    int spacePos = findFirstSpacePosAfterCommand(fullCommand);

    if (spacePos >= 0)
    {
        if (commandStart >= 0) commandName = fullCommand.substr(commandStart, spacePos - commandStart);

        int dataPos = findFirstNotEmptySymPos(fullCommand, spacePos + 1);

        if(dataPos >= 0)
        {
            commandData = fullCommand.substr(dataPos);
        }
    }
    else
    {
        if(commandStart >= 0) commandName = fullCommand.substr(commandStart);
    }
}

void splitCommand(std::wstring_view& fullCommand, int& commandStartPos, int& commandNameLastSym, int& dataFirstSymbol)
{
    commandStartPos = findFirstNotEmptySymPos(fullCommand);
    int spacePos = findFirstSpacePosAfterCommand(fullCommand);

    commandNameLastSym = spacePos - 1;

    if (spacePos >= 0)
    {
        int dataPos = findFirstNotEmptySymPos(fullCommand, spacePos + 1);

        dataFirstSymbol = dataPos;
        return;
    }

    dataFirstSymbol = -1;
}

int findFirstNotEmptySymPos(std::wstring_view& fullCommand, int startPos/* = 0*/)
{
    for(int i = startPos; i < (int)fullCommand.size(); i++)
    {
        if(fullCommand[i] != L' ')
        {
            return i;
        }
    }

    return -1;
}

int findFirstSpacePosAfterCommand(std::wstring_view& fullCommand)
{
    bool wasAlNumC = false;
    for (int i = 0; i < (int)fullCommand.size(); i++)
    {

        if(!wasAlNumC && iswalnum(fullCommand[i]))
        {
            wasAlNumC = true;
            continue;
        }

        if (fullCommand[i] == L' ' && wasAlNumC)
        {
            return i;
        }
    }
    return -1;
}
