//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include <iostream>
#include <cmath>

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
    int num = processor.getRuntimeData().get();
    std::cout << num << std::endl;

    return WellCode;
}

int push_command(Processor& processor, int codedCommandNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedCommandNum, NULL, NULL, &hasRamCall);

    evalExpression(processor, codedCommandNum);

    if(hasRamCall)
    {
        int ramPos = processor.getRuntimeData().peek();

        int ramData = processor.getAppRAM()[ramPos];

        processor.getRuntimeData().push(ramData);
    }

    return WellCode;
}

int evalExpression(Processor& processor, int codedCommandNum)
{
    bool hasRegister = false;
    bool hasConst = false;

    decodeNumberRepresentation(codedCommandNum, &hasConst, &hasRegister);
    if (hasConst)
    {
        int constNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().getAppData().push(constNum);
    }

    if (hasRegister)
    {
        int regNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().getAppData().push(processor.getAppRegister().getReg(regNum));
    }

    if (hasConst && hasRegister)
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

    a = processor.getRuntimeData().peek();
    b = processor.getRuntimeData().peek();

    a = a + b;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int sub_command(Processor& processor, int codedCommandNum)
{

    int a = 0, b = 0;

    a = processor.getRuntimeData().peek();
    b = processor.getRuntimeData().peek();

    a = b - a;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int mul_command(Processor& processor, int codedCommandNum)
{
    int a = 0, b = 0;

    a = processor.getRuntimeData().peek();
    b = processor.getRuntimeData().peek();

    a = a * b;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}

int div_command(Processor& processor, int codedCommandNum)
{
    int a = 0, b = 0;

    a = processor.getRuntimeData().peek();
    b = processor.getRuntimeData().peek();

    a = b / a;

    processor.getRuntimeData().getAppData().push(a);

    return WellCode;
}


int pop_command(Processor& processor, int codedCommandNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedCommandNum, NULL, NULL, &hasRamCall);

    if(hasRamCall)
    {
        evalExpression(processor, codedCommandNum);
        int ramPos = processor.getRuntimeData().peek();
        int& ramData = processor.getAppRAM()[ramPos];

        ramData = processor.getRuntimeData().peek();

        return WellCode;
    }

    int* regNum = processor.getCommandData().peek<int>();

    int data = processor.getRuntimeData().peek();

    processor.getAppRegister().setReg(*regNum, data);

    return WellCode;
}

int commonJmpFnc(Processor& processor, bool needToJump)
{
    int jmpPos = *processor.getCommandData().peek<int>();

    if (needToJump)
    {
        bool res = processor.getCommandData().setCurrPos(jmpPos);

        if (!res)
        {
            throw std::exception("Попытка перепрыгнуть на несуществующюю позицию");
            return MachineCodeOutOfBound;
        }
    }

    return WellCode;
}

int jmp_command(Processor& processor, int codedCommandNum)
{
    return commonJmpFnc(processor, true);
}

int get2ElementsFromStack(int* a, int* b, Processor& processor)
{
    try
    {
        *b = processor.getRuntimeData().peek();
        *a = processor.getRuntimeData().peek();
    }
    catch (...)
    {
        return EmptyStackGetError;
    }
    return WellCode;
}

int ja_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a > b;

    return commonJmpFnc(processor, expressionRes);
}

int jae_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a >= b;

    return commonJmpFnc(processor, expressionRes);
}

int jb_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a < b;

    return commonJmpFnc(processor, expressionRes);
}

int jbe_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a <= b;

    return commonJmpFnc(processor, expressionRes);
}

int je_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a == b;

    return commonJmpFnc(processor, expressionRes);
}

int jne_command(Processor& processor, int codedCommandNum)
{
    int b = 0, a = 0;

    int res = get2ElementsFromStack(&a, &b, processor);

    if (res != WellCode) return res;

    bool expressionRes = a != b;

    return commonJmpFnc(processor, expressionRes);
}

int sqrt_command(Processor& processor, int codedCommandNum)
{
    int a = processor.getRuntimeData().peek();

    double res = sqrt(a);

    processor.getRuntimeData().push((int)res);

    return WellCode;
}