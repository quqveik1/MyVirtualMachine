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
    CommandDataFloatType num = 0;
    std::cin >> num;
    CommandDataType pnum = convNum(num);
    processor.getRuntimeData().push(pnum);

    return ErrorCode::WellCode;
}

ErrorCode out_command(Processor& processor, int codedCommandNum)
{
    bool hasConst = false;
    decodeNumberRepresentation(codedCommandNum, &hasConst);

    if (!hasConst)
    {
        CommandDataType num = processor.getRuntimeData().peek();
        std::cout << deConvNum<CommandDataFloatType>(num) << std::endl;

        return ErrorCode::WellCode;
    }

    int beforeJmp = processor.getCommandData().getCurrPos() + sizeof(CommandDataType);

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
        CommandDataType ramPos = deConvNum<CommandDataType>(processor.getRuntimeData().peek());

        CommandDataType ramData = processor.getAppRAM()[ramPos];

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
        CommandDataType constNum = *processor.getCommandData().peek<CommandDataType>();
        processor.getRuntimeData().push(constNum);
    }

    if (hasRegister)
    {
        CommandDataType regNum = *processor.getCommandData().peek<CommandDataType>();
        processor.getRuntimeData().push(processor.getAppRegister().getReg((int)deConvNum<CommandDataType>(regNum)));
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
    CommandDataType a1 = 0, b1 = 0;

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
    CommandDataFloatType a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a + b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode sub_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

    get2Arg(a, b, processor);

    a = b - a;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode mul_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

    get2Arg(a, b, processor);

    a = a * b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode div_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

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
        CommandDataType ramPos = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
        CommandDataType& ramData = processor.getAppRAM()[ramPos];

        try
        {
            ramData = processor.getRuntimeData().peek();
        }
        catch (...)
        {
            return ErrorCode::EmptyStackGetError;
        }
            

        return ErrorCode::WellCode;
    }

    CommandDataType regNum = deConvNum<CommandDataType>(*processor.getCommandData().peek<CommandDataType>());

    CommandDataFloatType data = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());

    processor.getAppRegister().setReg((int)regNum, convNum(data));

    return ErrorCode::WellCode;
}

ErrorCode commonJmpFnc(Processor& processor, bool needToJump, int codedNum)
{
    evalRamExpression(processor, codedNum);
    CommandDataType jmpPos = deConvNum<CommandDataType>(processor.getRuntimeData().peek());

    if (needToJump)
    {
        doJump(processor, jmpPos);
    }

    return ErrorCode::WellCode;
}

ErrorCode doJump(Processor& processor, CommandDataType pos)
{
    bool res = processor.getCommandData().setCurrPos((int)pos);

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

ErrorCode ja_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a > b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jae_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a >= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jb_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a < b;

    CommandDataType deconvDenom = deConvNum<CommandDataType>(processor.getAppRAM()[2]);
    CommandDataType i = deConvNum<CommandDataType>(processor.getAppRAM()[6]);
    CommandDataType currIndex = deConvNum<CommandDataType>(processor.getAppRAM()[7]);
    CommandDataFloatType res = deConvNum<CommandDataFloatType>(processor.getAppRAM()[0]);

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jbe_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a <= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode je_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a == b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jne_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    get2Arg(b, a, processor);

    bool expressionRes = a != b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode sqrt_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());

    double res = sqrt(a);

    processor.getRuntimeData().push(convNum(res));

    return ErrorCode::WellCode;
}

ErrorCode sin_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());

    CommandDataFloatType res = (CommandDataFloatType)sinus((CommandDataFloatType)a);

    processor.getRuntimeData().push(convNum(res));

    return ErrorCode::WellCode;
}

unsigned long long factorial(int n)
{
    static const int cacheLen = 2 * defaultSinLen + 1;
    static unsigned long long cache[cacheLen + 1] {1, 1};

    if (cache[n] > 0) return cache[n];

    int lastValidFac = 1;

    for (int i = n - 1; i >= 1; i--)
    {
        if(cache[i] > 0)
        {
            lastValidFac = i;
            break;
        }
    }

    for (int i = lastValidFac + 1; i <= n; i++)
    {
        cache[i] = cache[i - 1] * i;
    }

    return cache[n];
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
    processor.getCallStack().push(processor.getCommandData().getCurrPos() + sizeof(CommandDataType));
    commonJmpFnc(processor, true, codedCommandNum);

    return ErrorCode::WellCode;
}

ErrorCode ret_command(Processor& processor, int codedCommandNum)
{
    CommandDataType lastPos = processor.getCallStack().peek();

    doJump(processor, lastPos);

    return ErrorCode::WellCode;
}

//!!!
ErrorCode neg_command(Processor& processor, int codedCommandNum)
{
    CommandDataType num = processor.getRuntimeData().peek();

    num = deConvNum<CommandDataType>(num);

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

    processor.getCommandData().setCurrPos(processor.getCommandData().getCurrPos() - sizeof(CommandDataType));
    processor.getBreakpoints().setRewriteBreakpoint(processor.getCommandData().getCurrPos());
    ErrorCode res = processor.getBreakpoints().removeOnlyFromCode(processor.getCommandData().getCurrPos());

    if (res != ErrorCode::WellCode) return res;

    return ErrorCode::DebugBreakCode;
}

ErrorCode setpxl_command(Processor& processor, int codedCommandNum)
{
    unsigned char blue = deConvNum<unsigned char> (processor.getRuntimeData().peek());
    unsigned char green = deConvNum<unsigned char>(processor.getRuntimeData().peek());
    unsigned char red = deConvNum<unsigned char>  (processor.getRuntimeData().peek());

    CommandDataType y = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
    CommandDataType x = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
                     
    int color = convColor(red, green, blue);

    processor.getAppRAM().setPixel(x, y, color);

    return ErrorCode::WellCode;

}

ErrorCode rdsys_command(Processor& processor, int codedCommandNum)
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