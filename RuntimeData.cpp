//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include "RuntimeData.h"

#include <iomanip> 

#include "StackVector.cpp"
#include "FloatConvert.cpp"

std::vector<int> &RuntimeData::getAppData()
{
    return getData();
}

void RuntimeData::printStack(bool needToConvertToUserRepresentation/*= true*/)
{
    if (getData().empty())
    {
        std::cout << "Стек пуст" << std::endl;
                                                                                                                                                                                                 
        return;
    }

    std::cout << "Стек с начала до конца: \n";

    for(size_t i = 0; i < getData().size(); i++)
    {
        int data = getData()[i];

        if(needToConvertToUserRepresentation)
        {
            data = deConvNum<int>(data);
        }

        std::cout << std::setw(5) << std::setfill('0') << std::right << i << ": " << data << std::endl;
    }

    std::cout << "Конец стека\n\n";
}
