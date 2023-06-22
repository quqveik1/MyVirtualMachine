#pragma once

#include "FileListing.h"

int FileListing::getListingFileActiveStringIndex()
{
    return (int)getFileListing().size() - 1;
}

std::wstring& FileListing::getActiveFileListingString()
{
    return getFileListing()[getListingFileActiveStringIndex()];
};

void FileListing::addNewListingLine()
{
    getFileListing().resize(getFileListing().size() + 1);
}

std::wstring_view& FileListing::getActiveOriginaFileLine()
{
    return getOriginalFileLines()[getActiveOriginalCodeLineNum()];
};

void FileListing::saveInFile(std::wstring path)
{
    std::ofstream listing(path);
    saveText(getFileListing(), (int)getFileListing().size(), listing, false);
}