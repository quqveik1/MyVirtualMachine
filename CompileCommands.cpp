#pragma once

#include <exception>

#include "CompileCommands.h"


int push_compile(std::wstring_view& data, char** binaryData)
{
    if (!data.empty())
    {
        int* number = new int{};
        *number = _wtoi(data.data());
        *binaryData = (char*)number;

        return sizeof(int);
    }

    throw std::exception("data.empty()");
    return NULL;
}