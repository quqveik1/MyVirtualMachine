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
#include  "ListCommands.cpp"
#include "IR.cpp"

void convertToNum(std::wstring path)
{
    setlocale(LC_ALL, "russian");

    initCompileArr();
    initCommandsListingArr();

    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    IR ir;
    ir.getCommands().reserve(cLines);

    CompileData dataArr;
    dataArr.getData().reserve(cLines);

    FileListing fileListing(dataArr, lines, cLines);

    int runRes = interpretTextToIR(lines, dataArr, cLines, fileListing);

    if (runRes != WellCode)
    {
        std::cout << "Ошибка перевода в байтовый вид, код: " << runRes << "\n";
    }
    else
    {
        save2Files(lines, dataArr, fileListing, cLines, path);
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

/*
out адрес буквы

db abc
<=>
'a'
'b'
'c'
*/

void save2Files(std::wstring_view* oldLines, CompileData& dataArr, FileListing& fileListing, int cLines, std::wstring path)
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

    fileListing.saveInFile(listingPath);
}

void clearMem(std::wstring_view& fullText, std::wstring_view* oldLines)
{
    if(oldLines)         delete[] oldLines;

    if (fullText.data()) delete[] fullText.data();
}

int interpretText(std::wstring_view* oldLines, CompileData& dataArr, int cLines, FileListing& fileListing)
{
    for (int i = 0; i < cLines; i++)
    {
        int bytePosBefore = dataArr.getCurrPos();
        int bytePosAfter = bytePosBefore;

        int commandNum = 0;

        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        fileListing.setActiveOriginalCodeLineNum(i);

        if (commandName.size() > 0)
        {
            commandNum = getCommandNum(commandName);

            if (isCommandNumValid(commandNum))
            {
                COMMANDCOMPILETYPE fnc = commandsCompileArr[commandNum];

                if (fnc != NULL)
                {
                    int res = fnc(dataArr, commandNum, commandData);
                }
            }
            else
            {
                bool isWordLine = ifIsWordDoJob(oldLines[i], dataArr);
                if (!isWordLine)
                {
                    std::wcout << L"Ошибка в распозновании команды в строке (" << i << L") [" << commandName << L"]\n";
                    std::wcout << L"\"" << oldLines[i] << "\"\n";
                    return CommandReadErrorCode;
                }
            }
        }

        bytePosAfter = dataArr.getCurrPos();

        COMMANDLISTINGTYPE fnc = NULL;
        if (isCommandNumValid(commandNum))
        {
            fnc = commandsListingArr[commandNum];
        }

        if(fnc == NULL)
        {
            default_listing(fileListing, bytePosBefore, bytePosAfter);
        }
        else
        {
            fnc(fileListing, bytePosBefore, bytePosAfter);
        }


    }
    return WellCode;
}

bool ifIsWordDoJob(std::wstring_view& line, CompileData& data)
{
    std::wstring_view word;
    bool res = isWord(line, word);
    if (res)
    {
        data.getWordSearch().pushWord(word);
    }

    return res;
}

bool isWord(std::wstring_view& line, std::wstring_view& word)
{
    int wordStart = findFirstNotEmptySymPos(line);
    if (wordStart < 0) return false;

    int wordFinish = (int)line.rfind(L':');
    if(wordFinish <= 0) return false;

    word = line.substr(wordStart, wordFinish - wordStart);

    bool res = isJmpWord(word);

    return res;
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
        int lastCommandPos = findLastLineSymbol(fullCommand);

        if(dataPos >= 0 && lastCommandPos >= 0)
        {
            commandData = fullCommand.substr(dataPos, lastCommandPos - dataPos + 1);
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

int findLastLineSymbol(std::wstring_view& fullCommand)
{
    for(size_t i = fullCommand.size() - 1; i >= 0; i--)
    {
        if(!iswspace(fullCommand[i]))
        {
            return (int)i;
        }
    }

    return -1;
}
