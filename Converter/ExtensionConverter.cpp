#pragma once
#include "ExtensionConverter.h"

//extension without dot
int deleteExtension(std::wstring& fileName)
{
    size_t lastDotPos = fileName.rfind(L'.');

    if(lastDotPos != std::wstring::npos)
    {
        fileName.erase(lastDotPos);
        return 0;
    }

    return -1;
}

//extension without dot
int changeExtension(std::wstring& fileName, std::wstring newExtension)
{
    int res = deleteExtension(fileName);

    fileName += L".";
    fileName += newExtension;

    return res;
}
