#pragma once

#include "Converter.h"

#include <locale>
#include <cstdio>
#include <WStringFnc.cpp>

#include "Commands/Compile1Commands.cpp"
#include "../FileHeader/FileHeader.h"
#include "Bin/BinCompileData.cpp"
#include "../Converter/ByteConverter.cpp"
#include "Commands/CompileArrs.cpp"
#include "../Constants/CommandConstants.cpp"
#include "../Converter/ExtensionConverter.cpp"
#include "FileListing.cpp"
#include "IR/IR.cpp"
#include "Commands/Compile2Commands.cpp"
#include "../Common/StackFunc.cpp"
#include "Parser/ParseCommand.cpp"
#include "../FileHeader/FileHeader.cpp"

void compile(std::string& path, bool needToCreateFileListing/* = true*/)
{
    setlocale(LC_ALL, "russian");

    init1CompileArr();
    init2CompileArr();

    std::wstring_view fullText{};
    try
    {
        readText(path, &fullText);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Error opening file for compiltation\n";

        return;
    }

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    IR ir;
    ir.getCommands().reserve(cLines);

    BinCompileData binCompileData;
    binCompileData.getData().reserve(cLines);

    FileListing fileListing(binCompileData, lines, cLines, ir, needToCreateFileListing);

    ErrorCode irRes = createIR(lines, ir, cLines, fileListing);
    if (printAndFinish(irRes, L"Error translating to intermediate representation, code: ", fullText, lines)) return;

    fileListing.end1Part();
    std::cout << "Intermediate layer successfully created\n";

    ErrorCode binRunRes = irToBin(ir, binCompileData, fileListing);
    if (printAndFinish(binRunRes, L"Error translating to binary representation, code: ", fullText, lines)) return;

    fileListing.end2Part();

    ErrorCode finalListing = fileListing.createFinalCodeListing();

    if (printAndFinish(finalListing, L"Error creating final code listing file: ", fullText, lines)) return;

    save2Files(binCompileData, fileListing, path);

    clearMem(fullText, lines);

    std::cout << "Compilation completed successfully\n";
}


bool printAndFinish(ErrorCode res, std::wstring str, std::wstring_view& fullText, std::wstring_view* lines)
{
    if (res != ErrorCode::WellCode)
    {
        std::wcout << str << (int)res << L"\n";
        clearMem(fullText, lines);
        return true;
    }

    return false;
}

//‘ормат номера команд:
//8765 4321
//0mri ####
//0001 1001
//Ќовый синтаксис(складывает)
//push ax+10
//push 10+ax

/*
    индекс в массиве машинного кода
jmp 5

jamp above вызываетс€ если первое число больше второго
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

void save2Files(BinCompileData& dataArr, FileListing& fileListing, std::string& path)
{
    if (dataArr.getData().size() == 0) return;

    saveBinCompileData(dataArr, path);

    std::string listingPath = path;
    changeExtension(listingPath, (std::string)"lst");

    fileListing.saveInFile(listingPath);
}

void saveBinCompileData(BinCompileData& dataArr, std::string& path)
{
    std::string saveBinPath = path;
    changeExtension(saveBinPath, (std::string)"bin");

    std::ofstream file(saveBinPath, std::ios::binary);

    FileHeader fileHeader;
    fileHeader.setHashSum(&dataArr.getData()[0], dataArr.getData().size());

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

ErrorCode irToBin(IR& ir, BinCompileData& compileData, FileListing& fileListing)
{
    for(size_t i = 0; i < ir.getCommands().size(); i++)
    {
        size_t bytePosBefore = compileData.getCurrPos();
        size_t bytePosAfter = bytePosBefore;
        fileListing.addNewBinLineStart(bytePosBefore);

        CommandIR& commandIR = ir.getCommand((int)i);
        if (isCommandNumValid(commandIR.getCommandNum()))
        {
            COMMAND2COMPILETYPE fnc = commands2CompileArr[commandIR.getCommandNum()];

            ErrorCode res = ErrorCode::WellCode;

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
        fileListing.addNewBinLineFinish(bytePosAfter);

        fileListing.add2CompileCommand(commandIR, compileData, bytePosBefore, bytePosAfter);
    }

    return compileData.finishWork();
}

ErrorCode createIR(std::wstring_view* oldLines, IR& ir, int cLines, FileListing& fileListing)
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
            ErrorCode code = getCommandNum(commandNum, commandName);

            COMMAND1COMPILETYPE fnc = nullptr;

            if (code == ErrorCode::WellCode)
            {
                fnc = commands1CompileArr[commandNum];
            }
            else
            {
                bool isWordLine = isWord(oldLines[i], &commandData);
                if(isWordLine)
                {
                    fnc = commands1CompileArr[word_num];
                    commandNum = word_num;
                }
                else
                {
                    printLineError(ErrorCode::CommandReadErrorCode, i, oldLines[i]);
                    return ErrorCode::CommandReadErrorCode;
                }
            }

            ir.getActiveCommand().setCommandNum(commandNum);
            ir.getActiveCommand().setLinePos(i);

            ErrorCode res = ErrorCode::WellCode;

            if (fnc)
            {
                res = fnc(ir.getActiveCommand(), commandNum, commandData, ir);
            }
            else
            {
                res = default_1compile(ir.getActiveCommand(), commandNum, commandData, ir);
            }

            if (res != ErrorCode::WellCode)
            {
                printLineError(res, i, oldLines[i]);

                return res;
            }
        }

        fileListing.add1CompileCommand(ir.getActiveCommand());
    }

    return ir.finishIntermediateWork();
}

void printLineError(ErrorCode errorCode, int lineNum, std::wstring_view& line)
{
    std::wcout << L"Error [" << (int)errorCode << L"] in command recognition in line (" << lineNum << L")\n";
    std::wcout << L"\"" << line << "\"\n";
}

bool ifIsWordDoJob(std::wstring_view& line, BinCompileData& data)
{
    std::wstring_view word;
    bool res = isWord(line, &word);
    if (res)
    {
        //data.getLabelSearchBin().pushWord(word);
    }

    return res;
}

bool isWord(std::wstring_view& line, std::wstring_view* word/*= nullptr*/)
{
    int wordStart = findFirstNotEmptySymPos(line);
    if (wordStart < 0) return false;

    int wordFinish = (int)line.rfind(L':');
    if(wordFinish <= 0) return false;

    *word = line.substr(wordStart, (size_t)(wordFinish - wordStart));

    bool res = isJmpWord(*word);

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