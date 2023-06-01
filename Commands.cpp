//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include "StackFunc.cpp"
#include "CommandConstants.h"

int in_command(Processor& processor)
{
    int num = 0;
    std::cin >> num;
    processor.getRuntimeData().getAppData().push(num);

    return 0;
}

int out_command(Processor& processor)
{
    int num = peek(processor.getRuntimeData().getAppData());
    std::cout << num << std::endl;

    return 0;
}

int push_command(Processor& processor)
{
    int num = *processor.getCommandData().peek<int>();
    processor.getRuntimeData().getAppData().push(num);

    return 0;
}

int hlt_command(Processor& processor)
{
    return CommandBreakCode;
}

int add_command(Processor& processor)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = a + b;

    processor.getRuntimeData().getAppData().push(a);

    return 0;
}

int sub_command(Processor& processor)
{

    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = b - a;

    processor.getRuntimeData().getAppData().push(a);

    return 0;
}

int mul_command(Processor& processor)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = a * b;

    processor.getRuntimeData().getAppData().push(a);

    return 0;
}

int div_command(Processor& processor)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = b / a;

    processor.getRuntimeData().getAppData().push(a);

    return 0;
}




