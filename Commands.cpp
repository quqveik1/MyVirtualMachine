//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "Commands.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <thread>
#include <chrono>

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
        CommandDataType num = 0;
        try
        {
            num = processor.getRuntimeData().peek();
        }
        catch (...)
        {
            return ErrorCode::EmptyStackGetError;
        }

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
        CommandDataType ramPos = 0;
        try
        {
            ramPos = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
        }
        catch (...)
        {
            return ErrorCode::EmptyStackGetError;
        }

        CommandDataType ramData = 0;
        try
        {
            ramData = processor.getAppRAM()[ramPos];
        }
        catch (...)
        {
            return ErrorCode::RAMOutOfBounds;
        }

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
        CommandDataType constNum = 0;
        try
        {
            constNum = *processor.getCommandData().peek<CommandDataType>();
        }
        catch (...)
        {
            return ErrorCode::CommandDataReadError;
        }
        processor.getRuntimeData().push(constNum);
    }

    if (hasRegister)
    {

        CommandDataType regNum = 0;
        try
        {
            regNum = *processor.getCommandData().peek<CommandDataType>();
        }
        catch (...)
        {
            return ErrorCode::CommandDataReadError;
        }
        try
        {
            processor.getRuntimeData().push(processor.getAppRegister().getReg((int)deConvNum<CommandDataType>(regNum)));
        }
        catch (...)
        {
            return ErrorCode::RegisterNotFound;
        }
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

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    a = a + b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode sub_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

    try
    {
        get2Arg(a, b, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    a = b - a;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode mul_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    a = a * b;

    processor.getRuntimeData().push(convNum(a));

    return ErrorCode::WellCode;
}

ErrorCode div_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0, b = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    a = a / b;

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
        CommandDataType ramPos = 0;
        try
        {
            ramPos = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
        }
        catch (...)
        {
            return ErrorCode::EmptyStackGetError;
        }

        CommandDataType* ramData = &ramPos;
        try
        {
            ramData = &processor.getAppRAM()[ramPos];
        }
        catch (...)
        {
            return ErrorCode::RAMOutOfBounds;
        }

        try
        {
            *ramData = processor.getRuntimeData().peek();
        }
        catch (...)
        {
            return ErrorCode::EmptyStackGetError;
        }
            

        return ErrorCode::WellCode;
    }

    CommandDataType regNum = 0;
    try
    {
        regNum = deConvNum<CommandDataType>(*processor.getCommandData().peek<CommandDataType>());
    }
    catch (...)
    {
        return ErrorCode::CommandEndFileErrorCode;
    }

    CommandDataFloatType data = 0;
    try
    {
        data = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    try
    {
        processor.getAppRegister().setReg((int)regNum, convNum(data));
    }
    catch (...)
    {
        return ErrorCode::RegisterNotFound;
    }

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

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    bool expressionRes = a > b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jae_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    bool expressionRes = a >= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jb_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

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

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    bool expressionRes = a <= b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode je_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    bool expressionRes = a == b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode jne_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType b = 0, a = 0;

    try
    {
        get2Arg(b, a, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    bool expressionRes = a != b;

    return commonJmpFnc(processor, expressionRes, codedCommandNum);
}

ErrorCode sqrt_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType a = 0;
    try
    {
        a = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    double res = sqrt(a);

    processor.getRuntimeData().push(convNum(res));

    return ErrorCode::WellCode;
}

ErrorCode sin_command(Processor& processor, int codedCommandNum)
{

    CommandDataFloatType a = 0;
    try
    {
        a = deConvNum<CommandDataFloatType>(processor.getRuntimeData().peek());
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

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

//Debug:
// c++ -  146ms
// asm - 2851ms
//Release:
// c++ -    5ms
// asm -   94ms
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

ErrorCode fmod_command(Processor& processor, int codedCommandNum)
{
    CommandDataFloatType divisible = 0, divider = 0;

    try
    {
        get2Arg(divider, divisible, processor);
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    CommandDataFloatType ans = std::fmod(divisible, divider);
    processor.getRuntimeData().push(convNum(ans));

    return ErrorCode::WellCode;
}

ErrorCode call_command(Processor& processor, int codedCommandNum)
{
    processor.getCallStack().push(processor.getCommandData().getCurrPos() + sizeof(CommandDataType));
    commonJmpFnc(processor, true, codedCommandNum);

    return ErrorCode::WellCode;
}

ErrorCode ret_command(Processor& processor, int codedCommandNum)
{
    CommandDataType lastPos = 0;
    try
    {
        lastPos = processor.getCallStack().peek();
    }
    catch (...)
    {
        return ErrorCode::EmptyCallStackReturnError;
    }

    doJump(processor, lastPos);

    return ErrorCode::WellCode;
}

//!!!
ErrorCode neg_command(Processor& processor, int codedCommandNum)
{      
    CommandDataType num = 0;
    try
    {
        num = processor.getRuntimeData().peek();
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    num = deConvNum<CommandDataType>(num);

    num *= -1;

    num = convNum(num);

    processor.getRuntimeData().push(num);

    return ErrorCode::WellCode;
}

//if has constant it is runtime breakpoint
ErrorCode into_command(Processor& processor, int codedCommandNum)
{
    return ErrorCode::WellCode;
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
    unsigned char blue = 0, green = 0, red = 0;

    CommandDataType x = 0, y = 0;

    try
    {
        blue = deConvNum<unsigned char>(processor.getRuntimeData().peek());
        green = deConvNum<unsigned char>(processor.getRuntimeData().peek());
        red = deConvNum<unsigned char>(processor.getRuntimeData().peek());

        y = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
        x = deConvNum<CommandDataType>(processor.getRuntimeData().peek());
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }
                     
    int color = convColor(red, green, blue);

    processor.getAppRAM().setPixel(x, y, color);

    return ErrorCode::WellCode;

}

ErrorCode rdsys_command(Processor& processor, int codedCommandNum)
{
    int component = 0;
    try
    {
        component = *processor.getCommandData().peek<int>();
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

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

ErrorCode wait_command(Processor& processor, int codedCommandNum)
{
    CommandDataIntType length = 0;
    try
    {
        length = deConvNum< CommandDataIntType>(processor.getRuntimeData().peek());
    }
    catch (...)
    {
        return ErrorCode::EmptyStackGetError;
    }

    //Sleep(length);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    return ErrorCode::WellCode;
}