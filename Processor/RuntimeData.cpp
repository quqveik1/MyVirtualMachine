//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include "RuntimeData.h"

#include <iomanip> 

#include "../Common/StackVector.cpp"
#include "../Converter/FloatConvert.cpp"

std::vector<CommandDataType> &RuntimeData::getAppData()
{
    return getData();
}

ErrorCode RuntimeData::print(bool needToConvertToUserRepresentation/*= true*/)
{
    if (getData().empty())
    {
        std::cout << "Stack is empty" << std::endl;
                                                                                                                                                                                                 
        return ErrorCode::WellCode;
    }

    std::cout << "Stack from start to end: \n";

    for(size_t i = 0; i < getData().size(); i++)
    {
        CommandDataType data = getData()[i];
        std::cout << std::setw(5) << std::setfill('0') << std::right << std::hex << i << ": ";

        if(needToConvertToUserRepresentation)
        {
            double number = deConvNum<double>(data);
            std::cout << number << std::endl;
        }
        else
        {
            std::cout << data << std::endl;
        }
    }

    std::cout << "End of stack\n";

    return ErrorCode::WellCode;
}
