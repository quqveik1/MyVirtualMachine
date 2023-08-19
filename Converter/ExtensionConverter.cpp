#pragma once
#include "ExtensionConverter.h"

#include <string>

//extension without dot
template<typename STR>
int deleteExtension(STR& fileName)
{
    size_t lastDotPos = fileName.rfind('.');

    if(lastDotPos != STR::npos)
    {
        fileName.erase(lastDotPos);
        return 0;
    }

    return -1;
}

//extension without dot
template<typename STR>
int changeExtension(STR& fileName, STR newExtension)
{
    int res = deleteExtension(fileName);

    fileName += '.';
    fileName += newExtension;

    return res;
}
