//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Common/StackFunc.cpp"
#include "Constants/CommandConstants.h"
#include "Converter/ByteConverter.cpp"
#include "Converter/FloatConvert.cpp"
#include "Converter/ColorConverter.cpp"
#include "Constants/SystemInfo.cpp"

ErrorCode in_command(Processor& processor, int codedCommandNum)
{
    float num = 0;
    std::cin >> num;
    int pnum = convNum(num);
    processor.getRuntimeData().push(pnum);

    return ErrorCode::WellCode;
}

ErrorCode out_command(Processor& processor, int codedCommandNum)
{
    bool hasConst = false;
    decodeNumberRepresentation(codedCommandNum, &hasConst);

    if (!hasConst)
    {
        int num = processor.getRuntimeData().peek();
        std::cout << deConvNum<float>(num) << std::endl;

        return ErrorCode::WellCode;
    }

    int beforeJmp = processor.getCommandData().getCurrPos() + sizeof(int);

    commonJmpFnc(processor, true, codedCommandNum);

    wchar_t* str = processor.getCommandData().peek<wchar_t>();

    for(int i = 0; str[i]; i++)
    {
        std::wcout << str[i];
    }

    processor.getCommandData().setCurrPos(beforeJmp);

    return ErrorCode::WellCode;
}

ErrorCode callRam(Processor& processor, int codedNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedNum, NULL, NULL, &hasRamCall);

    if(hasRamCall)
    {
        int ramPos = deConvNum<int>(processor.getRuntimeData().peek());

        int ramData = processor.getAppRAM()[ramPos];

        processor.getRuntimeData().push(ramData);
    }
    return ErrorCode::WellCode;
}

ErrorCode evalRamExpression(Processor& processor, int codedNum)
{
    evalExpression(processor, codedNum);

    callRam(processor, codedNum);

    return ErrorCode::WellCode;
}

ErrorCode push_command(Processor& processor, int codedCommandNum)
{
    evalRamExpression(processor, codedCommandNum);

    return ErrorCode::WellCode;
}

ErrorCode evalExpression(Processor& processor, int codedCommandNum)
{
    bool hasRegister = false;
    bool hasConst = false;

    decodeNumberRepresentation(codedCommandNum, &hasConst, &hasRegister);
    if (hasConst)
    {
        int constNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().push(constNum);
    }

    if (hasRegister)
    {
        int regNum = *processor.getCommandData().peek<int>();
        processor.getRuntimeData().push(processor.getAppRegister().getReg(deConvNum<int>(regNum)));
    }

    if (hasConst && hasRegister)
    {
        add_command(processor, add_num);
    }

    return ErrorCode::WellCode;
}

template <typename T>
ErrorCode get2Arg(T& a, T& b, Processor& processor)
{
    int a1 = 0, b1 = 0;

    try
    {
        a1 = processor.getRuntimeData().peek();
        b1 = processor.getRuntimeData().peek();
    }
    catch(...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    a = deConvNum<T>(a1);
    b = deConvNum<T>(b1);

    return ErrorCode::WellCode;
}

ErrorCode hlt_command(Processor& processor, int codedCommandNum)
{
    return ErrorCode::CommandBreakCode;
}

ErrorCode add_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a + b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode sub_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = b - a;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode mul_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a * b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode div_command(Processor& processor, int codedCommandNum)
{
    float a = 0, b = 0;

    get2Arg(a, b, processor);

    a = b / a;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}


ErrorCode pop_command(Processor& processor, int codedCommandNum)
{
    bool hasRamCall = false;

    decodeNumberRepresentation(codedCommandNum, NULL, NULL, &hasRamCall);

    if(hasRamCall)
    {
        evalExpression(processor, codedCommandNum);
        int ramPos = deConvNum<int>(processor.getRuntimeData().peek());
        int& ramData = processor.getAppRAM()[ramPos];

        ramData = processor.getRuntimeData().peek();

        return ErrorCode::WellCode;
    }

    int regNum = deConvNum<int>(*processor.getCommandData().peek<int>());

    float data = deConvNum<float>(processor.getRuntimeData().peek());

    processor.getAppRegister().setReg(regNum, convNum(data));

    return ErrorCode::WellCode;
}

ErrorCode commonJmpFnc(Processor& processor, bool needToJump, int codedNum)
{
    evalRamExpression(processor, codedNum);
    int jmpPos = deConvNum<int>(processor.getRuntimeData().peek());

    if (needToJump)
    {
        doJump(processor, jmpPos);
    }

    return ErrorCode::WellCode;
}

ErrorCode doJump(Processor& processor, int pos)
{
    bool res = processor.getCommandData().setCurrPos(pos);

    if (!res)
    {
        throw std::exception("Попытка перепрыгнуть на несуществующюю позицию");
        return ErrorCode::MachineCodeOutOfBound;
    }

    return ErrorCode::WellCode;
}

ErrorCode jmp_command(Processor& processor, int codedCommandNum)
{
    return commonJmpFnc(processor, true, codedCommandNum);
}

ErrorCode get2ElementsFromStack(int* a, int* b, Processor& processor)
{
    try
    {
        *b = processor.getRuntimeData().peek();
        *a = processor.getRuntimeData().peek();
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }
    return ErrorCode::WellCode;
}

ErrorCode ja_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a > b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jae_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a >= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jb_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a < b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jbe_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a <= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode je_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a == b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jne_command(Processor& processor, int codedCommandNum)
{
    float b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a != b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode sqrt_command(Processor& processor, int codedCommandNum)
{
    float a = deConvNum<float>(processor.getRuntimeData().peek());

    double res = sqrt(a);

    processor.getRuntimeData().push(convNum(res));

    return ErrorCode::WellCode;
}

ErrorCode sin_command(Processor& processor, int codedCommandNum)
{
    float a = deConvNum<float>(processor.getRuntimeData().peek());

    float res = (float)sinus((float)a);

    processor.getRuntimeData().push(convNum(res));

    return ErrorCode::WellCode;
}

unsigned long long factorial(int n)
{
    static const int facsLen = 2 * defaultSinLen + 1;
    static unsigned long long facs[facsLen + 1]{};

    if (facs[n] > 0) return facs[n];

    facs[1] = 1;

    int lastValidFac = 1;

    for (int i = n - 1; i >= 1; i--)
    {
        if(facs[i] > 0)
        {
            lastValidFac = i;
            break;
        }
    }

    for (int i = lastValidFac + 1; i <= n; i++)
    {
        facs[i] = facs[i - 1] * i;
    }

    return facs[n];
}

//1! | 1    | * 1
//3! | 6    | * 2 * 3
//5! | 120  | * 4 * 5
//7! | 5040 | * 6 * 7

double sinus(double number, int len/* = defaultSinLen*/)
{
    double res = 0;

    number = std::fmod(number, 2 * M_PI);
    double sign = 1;

    long long denom = 1;

    double currNum = number;
    double numberSquared = number * number;

    for (int i = 0; i < len; i++)
    {
        int currIndex = 2 * i + 1;

        res     += sign * (currNum / denom);

        denom   *= (++currIndex);
        denom   *= (++currIndex);

        currNum *= numberSquared;

        sign    *= -1;
    }

    return res;
}

ErrorCode call_command(Processor& processor, int codedCommandNum)
{
    processor.getCallStack().push(processor.getCommandData().getCurrPos() + sizeof(int));
    commonJmpFnc(processor, true, codedCommandNum);

    return ErrorCode::WellCode;
}

ErrorCode ret_command(Processor& processor, int codedCommandNum)
{
    int lastPos = processor.getCallStack().peek();

    doJump(processor, lastPos);

    return ErrorCode::WellCode;
}

//!!!
ErrorCode neg_command(Processor& processor, int codedCommandNum)
{
    int num = processor.getRuntimeData().peek();

    num = deConvNum<int>(num);

    num *= -1;

    num = convNum(num);

    processor.getRuntimeData().push(num);

    return ErrorCode::WellCode;
}

//if has constant it is runtime breakpoint
ErrorCode into_command(Processor& processor, int codedCommandNum)
{
    bool hasConstant = false;
    codedCommandNum = decodeNumberRepresentation(codedCommandNum, &hasConstant);

    if(!hasConstant) return ErrorCode::DebugBreakCode;

    processor.getCommandData().setCurrPos(processor.getCommandData().getCurrPos() - sizeof(int));
    processor.getBreakpoints().setRewriteBreakpoint(processor.getCommandData().getCurrPos());
    ErrorCode res = processor.getBreakpoints().removeOnlyFromCode(processor.getCommandData().getCurrPos());

    if (res != ErrorCode::WellCode) return res;

    return ErrorCode::DebugBreakCode;
}

ErrorCode setpxl_command(Processor& processor, int codedCommandNum)
{
    unsigned char blue = deConvNum<unsigned char>(processor.getRuntimeData().peek());
    unsigned char green = deConvNum<char>(processor.getRuntimeData().peek());
    unsigned char red = deConvNum<unsigned char>(processor.getRuntimeData().peek());

    int y = deConvNum<int>(processor.getRuntimeData().peek());
    int x = deConvNum<int>(processor.getRuntimeData().peek());
                     
    int color = convColor(red, green, blue);

    processor.getAppRAM().setPixel(x, y, color);

    return ErrorCode::WellCode;

}

ErrorCode si_command(Processor& processor, int codedCommandNum)
{
    int component = *processor.getCommandData().peek<int>();

    if(component == vsizex_num)
    {
        processor.getRuntimeData().push(convNum(processor.getAppRAM().xSize));

        return ErrorCode::WellCode;
    }
    else if (component == vsizey_num)
    {
        processor.getRuntimeData().push(convNum(processor.getAppRAM().ySize));

        return ErrorCode::WellCode;
    }

    return ErrorCode::SystemComponentNotFounded;
}