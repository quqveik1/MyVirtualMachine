//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include "StackFunc.cpp"
#include "CommandConstants.h"

int in_command(RuntimeAppData& appData, std::wstring_view & commandData)
{
    int num = 0;
    std::cin >> num;
    appData.getAppData().push(num);

    return 0;
}

int out_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    int num = peek(appData.getAppData());
    std::cout << num << std::endl;

    return 0;
}

int push_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    int num = 0;
    num = _wtoi(commandData.data());
    appData.getAppData().push(num);

    return 0;
}

int hlt_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    return CommandBreakCode;
}

int add_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = a + b;

    appData.getAppData().push(a);

    return 0;
}

int sub_command(RuntimeAppData& appData, std::wstring_view& commandData)
{

    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = b - a;

    appData.getAppData().push(a);

    return 0;
}

int mul_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = a * b;

    appData.getAppData().push(a);

    return 0;
}

int div_command(RuntimeAppData& appData, std::wstring_view& commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = b / a;

    appData.getAppData().push(a);

    return 0;
}




