#pragma once

#include "InteractiveCommands.h"

#include "../Processor/Register/RegisterCompile.h"
#include "../Common/StringViewExtension.cpp"

ErrorCode quit_command(Processor& processor, InteractiveCode& code, std::wstring& data)
{
    code = InteractiveCode::ShutDownProgramm;
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
        std::cout << "Ошибка при выполении распечатки стека: " << res << std::endl;
    }
}

void printRuntimeInfoDissassembler(Processor& processor)
{
    int res = processor.getRuntimeInfoCollector().onError();
    if (res != WellCode)
    {
        std::cout << "Ошибка при выполении распечатки последних комманд: " << res << std::endl;
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

    code = ContinueAppExecuting;

    return WellCode;
}