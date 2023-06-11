//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include "RuntimeData.h"

std::stack<int> &RuntimeData::getAppData()
{
    return appData;
}


int RuntimeData::peek()
{
    return _peek(getAppData());
}

int RuntimeData::get()
{
    if (getAppData().empty())
    {
        std::cout << "������� ����� �� ������� ����� �������\n";
        return {};
    }
    return getAppData().top();
}

void RuntimeData::push(int obj)
{
    return getAppData().push(obj);
}
