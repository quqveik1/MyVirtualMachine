//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include <iostream>

#include "StackFunc.cpp"
#include "CommandConstants.h"
#include "ByteConverter.cpp"
#include "Register.cpp"

int in_command(Processor& processor, int codedCommandNum)
{
    int num = 0;
    std::cin >> num;
    processor.getRuntimeData().getAppData().push(num);

    return WellCode;
}

int out_command(Processor& processor, int codedCommandNum)
{
    int num = peek(processor.getRuntimeData().getAppData());
    std::cout << num << std::endl;

    return WellCode;
}

int push_command(Processor& processor, int codedCommandNum)
{
    bool hasRegister = false;
    bool hasConst = false;

    decodeNumberRepresentation(codedCommandNum, &hasConst, &hasRegister);

    if(hasConst)
    {
        int constNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().getAppData().push(constNum);
    }

    if(hasRegister)
    {
        int regNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().getAppData().push(processor.getAppRegister().getReg(regNum));
    }

    if(hasConst && hasRegister)
    {
        add_command(processor, innerCall_num);
    }

    return WellCode;
}

int hlt_command(Processor& processor, int codedCommandNum)
{
    return CommandBreakCode;
}

int add_command(Processor& processor, int codedCommandNum)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = a + b;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int sub_command(Processor& processor, int codedCommandNum)
{

    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = b - a;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int mul_command(Processor& processor, int codedCommandNum)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = a * b;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int div_command(Processor& processor, int codedCommandNum)
{
    int a = 0, b = 0;

    a = peek(processor.getRuntimeData().getAppData());
    b = peek(processor.getRuntimeData().getAppData());

    a = b / a;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}


int pop_command(Processor& processor, int codedCommandNum)
{
    int* regNum = processor.getCommandData().peek<int>();

    int data = peek(processor.getRuntimeData().getAppData());

    processor.getAppRegister().setReg(*regNum, data);

    return WellCode;
}

