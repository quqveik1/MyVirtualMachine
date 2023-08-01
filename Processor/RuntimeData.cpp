//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include "RuntimeData.h"

#include <iomanip> 

#include "../Common/StackVector.cpp"
#include "../Converter/FloatConvert.cpp"

std::vector<int> &RuntimeData::getAppData()
{
    return getData();
}

ErrorCode RuntimeData::print(bool needToConvertToUserRepresentation/*= true*/)
{
    if (getData().empty())
    {
        std::cout << "Стек пуст" << std::endl;
                                                                                                                                                                                                 
        return ErrorCode::WellCode;
    }

    std::cout << "Стек с начала до конца: \n";

    for(size_t i = 0; i < getData().size(); i++)
    {
        int data = getData()[i];
        std::cout << std::setw(5) << std::setfill('0') << std::right << std::hex << i << ": ";

        if(needToConvertToUserRepresentation)
        {
            float number = deConvNum<float>(data);
            std::cout << number << std::endl;
        }
        else
        {
            std::cout << data << std::endl;
        }
    }

    std::cout << "Конец стека\n";

    return ErrorCode::WellCode;
}
