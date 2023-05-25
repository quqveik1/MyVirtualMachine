#pragma once

#include <exception>

#include "CompileCommands.h"


char* push_compile(std::wstring_view& data)
{
    if (!data.empty())
    {
        int* number = new int{};
        *number = _wtoi(data.data());

        return (char*)number;
    }

    throw std::exception("data.empty()");
    return NULL;
}