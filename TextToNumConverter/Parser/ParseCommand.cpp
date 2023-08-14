#pragma once

#include "ParseCommand.h"

template <typename S>
void splitCommand(S& fullCommand, S& commandName, S& commandData)
{
    int commandStart = findFirstNotEmptySymPos(fullCommand);
    int spacePos = findFirstSpacePosAfterCommand(fullCommand);

    if (spacePos >= 0)
    {
        if (commandStart >= 0) commandName = fullCommand.substr(commandStart, (int)spacePos - commandStart);

        int dataPos = findFirstNotEmptySymPos(fullCommand, spacePos + 1);
        int lastCommandPos = findLastLineSymbol(fullCommand);

        if (dataPos >= 0 && lastCommandPos >= 0)
        {
            commandData = fullCommand.substr(dataPos, lastCommandPos - dataPos + 1);
        }
    }
    else
    {
        if (commandStart >= 0) commandName = fullCommand.substr(commandStart);
    }
}

template <typename S>
void splitCommand(S& fullCommand, int& commandStartPos, int& commandNameLastSym, int& dataFirstSymbol)
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

template <typename S>
int findFirstNotEmptySymPos(S& fullCommand, int startPos/* = 0*/)
{
    for (int i = startPos; i < (int)fullCommand.size(); i++)
    {
        if (fullCommand[i] != L' ' && fullCommand[i] != L'\t')
        {
            return i;
        }
    }

    return -1;
}

template <typename S>
int findFirstSpacePosAfterCommand(S& fullCommand)
{
    bool wasAlNumC = false;
    for (int i = 0; i < (int)fullCommand.size(); i++)
    {

        if (!wasAlNumC && iswalnum(fullCommand[i]))
        {
            wasAlNumC = true;
            continue;
        }

        if ((fullCommand[i] == L' ' || fullCommand[i] == L'\t') && wasAlNumC)
        {
            return i;
        }
    }
    return -1;
}

template <typename S>
int findLastLineSymbol(S& fullCommand)
{
    for (size_t i = fullCommand.size() - 1; i >= 0; i--)
    {
        if (!iswspace(fullCommand[i]) && fullCommand[i] != L'\t')
        {
            return (int)i;
        }
    }

    return -1;
}