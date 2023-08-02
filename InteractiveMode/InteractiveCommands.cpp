#pragma once

#include "InteractiveCommands.h"

#include "../Processor/Register/RegisterCompile.h"
#include "../Common/StringViewExtension.cpp"

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    code = ShutDownProgramm;
    return WellCode;
}

ErrorCode continue_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    code = ContinueAppExecuting;

    return WellCode;
}

ErrorCode info_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    if(data == L"r" || data == L"registers")
    {
        printRegisters(processor);
        return WellCode;
    }
    else if (data == L"s" || data == L"stack")
    {
        printRuntimeData(processor);
        return WellCode;
    }

    return CommandDataReadError;
}

ErrorCode backtrace_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    printCallStack(processor);
    return WellCode;
}

ErrorCode disassemble_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    printRuntimeInfoDissassembler(processor);
    return WellCode;
}

void printRegisters(Processor& processor)
{
    processor.getAppRegister().print();
}

void printRuntimeData(Processor& processor)
{
    int res = processor.getRuntimeData().print();
    if (res != WellCode)
    {
        std::cout << "������ ��� ��������� ���������� �����: " << res << std::endl;
    }
}

void printRuntimeInfoDissassembler(Processor& processor)
{
    int res = processor.getRuntimeInfoCollector().onError();
    if (res != WellCode)
    {
        std::cout << "������ ��� ��������� ���������� ��������� �������: " << res << std::endl;
    }
}

void printCallStack(Processor& processor)
{
    processor.getCallStack().print();
}

ErrorCode examine_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    int memPos = std::stoi(data, nullptr, 16);

    processor.getAppRAM().print(memPos);

    return WellCode;
}

ErrorCode set_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    std::wstring_view datav = data;

    std::wstring_view object{}, numStr{};

    splitCommand(datav, object, numStr);

    int regNum = getRegisterNumFromStr(object);

    try
    {
        float num = strToFloat<float>(numStr);
        int convNumber = convNum(num);

        if (isRegisterValid(regNum))
        {

            processor.getAppRegister().setReg(regNum, convNumber);

            return WellCode;
        }
        else
        {
            int pos = strToNum(object, 16);
            processor.getAppRAM()[pos] = convNumber;

            return WellCode;
        }
    }
    catch(std::exception e)
    {
        std::cout << e.what() << "\n";
    }

    return CommandDataReadError;
}

ErrorCode set_backtrace_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    return stack_universal_command(processor, code, data, processor.getCallStack(), false);
}

ErrorCode set_stack_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    return stack_universal_command(processor, code, data, processor.getRuntimeData());
}

ErrorCode stack_universal_command(Processor& processor, InteractiveCode& code, std::wstring& data, StackVector& stackVector, bool needToConvert/* = true*/)
{
    std::wstring_view datav = data;

    std::wstring_view object{}, numStr{};

    splitCommand(datav, object, numStr);

    int stackPos = -1;

    if (object == L"push")
    {
        stackPos = (int)stackVector.getData().size();

        stackVector.push(1329);
    }
    else if (object == L"pop")
    {
        try
        {
            stackVector.pop();
        }
        catch (std::runtime_error e)
        {
            std::cout << e.what() << "\n";
        }
        return WellCode;
    }
    else
    {
        try
        {
            stackPos = strToNum(object, 16);
        }
        catch (std::exception e)
        {
            std::cout << e.what() << "\n";
        }
    }

    try
    {
        float num = strToFloat<float>(numStr);
        int convNumber = (int)num;
        if(needToConvert) convNumber = convNum(num);

        int* ram = stackVector.at(stackPos);

        if (!ram) return RAMOutOfBounds;

        *ram = convNumber;

        return WellCode;
    }
    catch (std::exception e)
    {
        std::cout << e.what() << "\n";
    }

    return CommandDataReadError;
}

ErrorCode jump_interactive_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    if(data.empty())
    {
        code = ContinueAppExecuting;
        return WellCode;
    }

    int pos = strToNum(data, 16);

    bool res = processor.getCommandData().setCurrPos(pos);

    if (!res) return CommandDataReadError;

    return WellCode;
}

ErrorCode breakpoint_interactive_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    int breakPos = 0;
    try
    {
        breakPos = strToNum(data, 16);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return CommandDataReadError;
    }

    processor.getBreakpoints().add(breakPos);


    return WellCode;
}