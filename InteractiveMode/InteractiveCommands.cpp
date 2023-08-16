#pragma once

#include "InteractiveCommands.h"

#include "../Processor/Register/RegisterCompile.h"
#include "../Common/StringViewExtension.cpp"

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    code = ShutDownProgramm;
    return ErrorCode::WellCode;
}

ErrorCode continue_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    code = ContinueAppExecuting;

    return ErrorCode::WellCode;
}

ErrorCode info_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    if(data == L"r" || data == L"registers")
    {
        printRegisters(processor);
        return ErrorCode::WellCode;
    }
    else if (data == L"s" || data == L"stack")
    {
        printRuntimeData(processor);
        return ErrorCode::WellCode;
    }
    else if(hasThisCommand(breakpoint_intractive_str, data))
    {
        return info_breakpoint_command(processor);
    }

    return ErrorCode::CommandDataReadError;
}

ErrorCode info_breakpoint_command(Processor& processor)
{
    processor.getBreakpoints().print();
    return ErrorCode::WellCode;
}

ErrorCode backtrace_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    printCallStack(processor);
    return ErrorCode::WellCode;
}

ErrorCode disassemble_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    printRuntimeInfoDissassembler(processor);
    return ErrorCode::WellCode;
}

void printRegisters(Processor& processor)
{
    processor.getAppRegister().print();
}

void printRuntimeData(Processor& processor)
{
    ErrorCode res = processor.getRuntimeData().print();
    if (res != ErrorCode::WellCode)
    {
        std::cout << "Ошибка при выполении распечатки стека: " << std::dec << (int)res << std::endl;
    }
}

void printRuntimeInfoDissassembler(Processor& processor)
{
    ErrorCode res = processor.getRuntimeInfoCollector().onError();
    if (res != ErrorCode::WellCode)
    {
        std::cout << "Ошибка при выполении распечатки последних комманд: " << std::dec << (int)res << std::endl;
    }
}

void printCallStack(Processor& processor)
{
    processor.getCallStack().print();
}

ErrorCode delete_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    if(data.empty())
    {
        return processor.getBreakpoints().removeAll();
    }

    int breakNum = strToNum(data);

    return processor.getBreakpoints().removeByNumber(breakNum);
}

ErrorCode examine_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    int memPos = 0;
    try
    {
        memPos = std::stoi((std::wstring)data, nullptr, 16);
    }
    catch(...)
    {
        return ErrorCode::InteractiveCommandDataError;
    }

    processor.getAppRAM().print(memPos);

    return ErrorCode::WellCode;
}

ErrorCode set_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    std::wstring_view datav = data;

    std::wstring_view object{}, numStr{};

    splitCommand(datav, object, numStr);

    int regNum = 0;
    ErrorCode resCode = getRegisterNumFromStr(object, regNum);

    if (resCode != ErrorCode::WellCode) return resCode;

    try
    {
        CommandDataFloatType num = strToFloat<CommandDataFloatType>(numStr);
        CommandDataType convNumber = convNum(num);

        if (isRegisterValid(regNum))
        {

            processor.getAppRegister().setReg(regNum, convNumber);

            return ErrorCode::WellCode;
        }
        else
        {
            int pos = strToNum(object, 16);
            processor.getAppRAM()[pos] = convNumber;

            return ErrorCode::WellCode;
        }
    }
    catch(std::exception e)
    {
        std::cout << e.what() << "\n";
    }

    return ErrorCode::CommandDataReadError;
}

ErrorCode set_backtrace_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    return stack_universal_command(processor, code, data, processor.getCallStack(), false);
}

ErrorCode set_stack_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    return stack_universal_command(processor, code, data, processor.getRuntimeData());
}

ErrorCode stack_universal_command(Processor& processor, InteractiveCode& code, std::wstring_view& data, StackVector<CommandDataType>& stackVector, bool needToConvert/* = true*/)
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
        return ErrorCode::WellCode;
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
        CommandDataFloatType num = strToFloat<CommandDataFloatType>(numStr);
        CommandDataType convNumber = (CommandDataType)num;
        if(needToConvert) convNumber = convNum(num);

        CommandDataType* ram = stackVector.at(stackPos);

        if (!ram) return ErrorCode::RAMOutOfBounds;

        *ram = convNumber;

        return ErrorCode::WellCode;
    }
    catch (std::exception e)
    {
        std::cout << e.what() << "\n";
    }

    return ErrorCode::CommandDataReadError;
}

ErrorCode jump_interactive_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    if(data.empty())
    {
        code = ContinueAppExecuting;
        return ErrorCode::WellCode;
    }

    int pos = strToNum(data, 16);

    bool res = processor.getCommandData().setCurrPos(pos);

    if (!res) return ErrorCode::CommandDataReadError;

    return ErrorCode::WellCode;
}

ErrorCode breakpoint_interactive_command(Processor& processor, InteractiveCode& code, std::wstring_view& data)
{
    int breakPos = 0;
    try
    {
        breakPos = strToNum(data, 16);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return ErrorCode::CommandDataReadError;
    }

    processor.getBreakpoints().add(breakPos);


    return ErrorCode::WellCode;
}