#pragma once

#include <locale>
#include <cstdio>

#include "Converter.h"
#include "Compile1Commands.cpp"
#include "../FileHeader.h"
#include "BinCompileData.cpp"
#include "../ByteConverter.cpp"
#include "../FncArrs.cpp"
#include "WStringFnc.cpp"
#include "../CommandConstants.cpp"
#include "../ExtensionConverter.cpp"
#include "FileListing.cpp"
#include "IR.cpp"
#include "Compile2Commands.cpp"

void convertToNum(std::wstring path)
{
    setlocale(LC_ALL, "russian");

    init1CompileArr();
    init2CompileArr();

    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    IR ir;
    ir.getCommands().reserve(cLines);

    BinCompileData binCompileData;
    binCompileData.getData().reserve(cLines);

    FileListing fileListing(binCompileData, lines, cLines, ir);

    int runRes = createIR(lines, ir, cLines, fileListing);

    if (runRes != WellCode)
    {
        std::wcout << L"Ошибка перевода в байтовый вид, код: " << runRes << L"\n";
        clearMem(fullText, lines);
        return;
    }

    fileListing.end1Part();

    int binRunRes = irToBin(ir, binCompileData, fileListing);

    save2Files(lines, binCompileData, fileListing, cLines, path);

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

void save2Files(std::wstring_view* oldLines, BinCompileData& dataArr, FileListing& fileListing, int cLines, std::wstring path)
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

int irToBin(IR& ir, BinCompileData& compileData, FileListing& fileListing)
{

    for(size_t i = 0; i < ir.getCommands().size(); i++)
    {
        int bytePosBefore = compileData.getCurrPos();
        int bytePosAfter = bytePosBefore;

        CommandIR& commandIR = ir.getCommand((int)i);
        if (isCommandNumValid(commandIR.getCommandNum()))
        {
            COMMAND2COMPILETYPE fnc = commands2CompileArr[commandIR.getCommandNum()];

            int res = WellCode;

            if(fnc)
            {
                res = fnc(commandIR, ir, compileData);
            }
            else
            {
                res = default_2compile(commandIR, ir, compileData);
            }
        }

        bytePosAfter = compileData.getCurrPos();

        fileListing.add2CompileCommand(commandIR, bytePosBefore, bytePosAfter);
        

    }

    return WellCode;
}

int createIR(std::wstring_view* oldLines, IR& ir, int cLines, FileListing& fileListing)
{
    for (int i = 0; i < cLines; i++)
    {

        int commandNum = 0;

        std::wstring_view commandName{};
        std::wstring_view commandData{};
        splitCommand(oldLines[i], commandName, commandData);

        ir.addNewCommand();
        ir.getActiveCommand().setLine(&oldLines[i]);
        

        if (commandName.size() > 0)
        {
            commandNum = getCommandNum(commandName);
            ir.getActiveCommand().setCommandNum(commandNum);

            if (isCommandNumValid(commandNum))
            {
                COMMAND1COMPILETYPE fnc = commands1CompileArr[commandNum];

                int res = WellCode;

                if (fnc)
                {
                    res = fnc(ir.getActiveCommand(), commandNum, commandData);
                }
                else
                {
                    res = default_1compile(ir.getActiveCommand(), commandNum, commandData);
                }

                if(res != WellCode)
                {
                    printError(res, i, oldLines[i]);
                }
            }
            else
            {
                //bool isWordLine = ifIsWordDoJob(oldLines[i], dataArr);
                if (true)
                {
                    printError(CommandReadErrorCode, i, oldLines[i]);
                    return CommandReadErrorCode;
                }
            }
        }

        fileListing.add1CompileCommand(ir.getActiveCommand());


    }
    return WellCode;
}

void printError(int errorCode, int lineNum, std::wstring_view& line)
{
    std::wcout << L"Ошибка ["<< errorCode <<L"] в распозновании команды в строке (" << lineNum << L")\n";
    std::wcout << L"\"" << line << "\"\n";
}

bool ifIsWordDoJob(std::wstring_view& line, BinCompileData& data)
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

    word = line.substr(wordStart, (size_t)(wordFinish - wordStart));

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
