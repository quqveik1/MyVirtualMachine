// TextToNumConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "../../StringSort/WStringFnc.cpp"
#include "../ReadCommands.cpp"

int main()
{

}

void convertToNum(std::wstring path)
{
    std::wstring_view fullText{};
    readText(path, &fullText);

    std::wstring_view* lines = NULL;

    int cLines = separateTextByLinesToArr(fullText, &lines);

    std::wstring* newLines = new std::wstring[cLines]{};

}

void interpretText(std::wstring_view* oldLines, std::wstring* newLines, int cLines)
{
    std::wstring_view commandName{};
    std::wstring_view commandData{};

    for (int i = 0; i < cLines; i++)
    {
        splitCommand(oldLines[i], commandName, commandData);

    }
}

int getCommandNum(std::wstring_view& commandName)
{
    int res = commandError_num;
    if (_wcsnicmp(commandName.data(), in_str, commandName.size()) == 0)
    {
        
    }

    else if (_wcsnicmp(commandName.data(), out_str, commandName.size()) == 0)
    {
        res = out_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), push_str, commandName.size()) == 0)
    {
        res = push_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), hlt_str, commandName.size()) == 0)
    {
        res = hlt_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), add_str, commandName.size()) == 0)
    {
        res = add_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), sub_str, commandName.size()) == 0)
    {
        res = sub_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), mul_str, commandName.size()) == 0)
    {
        res = mul_command(AppRuntimeData, commandData);
    }

    else if (_wcsnicmp(commandName.data(), div_str, commandName.size()) == 0)
    {
        res = div_command(AppRuntimeData, commandData);
    }
}
