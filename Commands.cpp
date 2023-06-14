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
#include "FloatConvert.cpp"

int in_command(Processor& processor, int codedCommandNum)
{
    float num = 0;
    std::cin >> num;
    int pnum = convNum(num);
    processor.getRuntimeData().getAppData().push(pnum);

    return WellCode;
}

int out_command(Processor& processor, int codedCommandNum)
{
    int num = processor.getRuntimeData().get();
    std::cout << deConvNum<float>(num) << std::endl;

    return WellCode;
}

int callRam(Processor& processor, int codedNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedNum, NULL, NULL, &hasRamCall);

    if(hasRamCall)
    {
        int ramPos = deConvNum<int>(processor.getRuntimeData().peek());

        int ramData = processor.getAppRAM()[ramPos];

        processor.getRuntimeData().push(ramData);
    }
    return WellCode;
}

int evalRamExpression(Processor& processor, int codedNum)
{
    evalExpression(processor, codedNum);

    callRam(processor, codedNum);

    return WellCode;
}

int push_command(Processor& processor, int codedCommandNum)
{
    

    evalRamExpression(processor, codedCommandNum);

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
        processor.getRuntimeData().getAppData().push(processor.getAppRegister().getReg(deConvNum<int>(regNum)));
    }

    if (hasConst && hasRegister)
    {
        add_command(processor, innerCall_num);
    }

    return WellCode;
}

template <typename T>
void get2Arg(T& a, T& b, Processor& processor)
{
    int a1 = 0, b1 = 0;

    a1 = processor.getRuntimeData().peek();
    b1 = processor.getRuntimeData().peek();

    a = deConvNum<T>(a1);
    b = deConvNum<T>(b1);
}

int hlt_command(Processor& processor, int codedCommandNum)
{
    return CommandBreakCode;
}

int add_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a + b;

    processor.getRuntimeData().getAppData().push(convNum(a));

    return WellCode;
}

int sub_command(Processor& processor, int codedCommandNum)
{

    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = b - a;

    processor.getRuntimeData().getAppData().push(convNum(a));

    return WellCode;
}

int mul_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a * b;

    processor.getRuntimeData().getAppData().push(convNum(a));

    return WellCode;
}

int div_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = b / a;

    processor.getRuntimeData().getAppData().push(convNum(a));

    return WellCode;
}


int pop_command(Processor& processor, int codedCommandNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedCommandNum, NULL, NULL, &hasRamCall);

    if(hasRamCall)
    {
        evalExpression(processor, codedCommandNum);
        int ramPos = deConvNum<int>(processor.getRuntimeData().peek());
        int& ramData = processor.getAppRAM()[ramPos];

        ramData = processor.getRuntimeData().peek();

        return WellCode;
    }

    int regNum = deConvNum<int>(*processor.getCommandData().peek<int>());

    float data = deConvNum<float>(processor.getRuntimeData().peek());

    processor.getAppRegister().setReg(regNum, convNum(data));

    return WellCode;
}

int commonJmpFnc(Processor& processor, bool needToJump, int codedNum)
{
    evalRamExpression(processor, codedNum);
    int jmpPos = deConvNum<int>(processor.getRuntimeData().peek());

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
    return commonJmpFnc(processor, true, codedCommandNum);
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
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a > b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int jae_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a >= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int jb_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a < b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int jbe_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a <= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int je_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a == b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int jne_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a != b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

int sqrt_command(Processor& processor, int codedCommandNum)
{
    float a = deConvNum<float>(processor.getRuntimeData().peek());

    double res = sqrt(a);

    processor.getRuntimeData().push(convNum(res));

    return WellCode;
}