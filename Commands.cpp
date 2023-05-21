//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include "StackFunc.cpp"
#include "CommandConstants.h"

int in_command(RuntimeData& appData, char* commandData)
{
    int num = 0;
    std::cin >> num;
    appData.getAppData().push(num);

    return 0;
}

int out_command(RuntimeData& appData, char* commandData)
{
    int num = peek(appData.getAppData());
    std::cout << num << std::endl;

    return 0;
}

int push_command(RuntimeData& appData, char* commandData)
{
    int num = 0;
    appData.getAppData().push(num);

    return 0;
}

int hlt_command(RuntimeData& appData, char* commandData)
{
    return CommandBreakCode;
}

int add_command(RuntimeData& appData, char* commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = a + b;

    appData.getAppData().push(a);

    return 0;
}

int sub_command(RuntimeData& appData, char* commandData)
{

    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = b - a;

    appData.getAppData().push(a);

    return 0;
}

int mul_command(RuntimeData& appData, char* commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = a * b;

    appData.getAppData().push(a);

    return 0;
}

int div_command(RuntimeData& appData, char* commandData)
{
    int a = 0, b = 0;

    a = peek(appData.getAppData());
    b = peek(appData.getAppData());

    a = b / a;

    appData.getAppData().push(a);

    return 0;
}




