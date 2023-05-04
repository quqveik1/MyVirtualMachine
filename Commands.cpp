//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"
#include "CommandConstants.h"

int in_command(RuntimeAppData& appData, std::string_view commandData)
{
    int num = 0;
    std::cin >> num;
    appData.getAppData().push(num);

    return 0;
}

int out_command(RuntimeData& appData, std::string_view commandData)
{
    int num = appData.getAppData().front();
    std::cout << num;
    appData.getAppData().pop();

    return 0;
}

int push_command(RuntimeAppData& appData, std::string_view commandData)
{
    int num = 0;
    num = atoi(commandData.data());
    appData.getAppData().push(num);

    return 0;
}

int hlt_command(RuntimeAppData& appData, std::string_view commandData)
{
    return CommandBreakCode;
}



