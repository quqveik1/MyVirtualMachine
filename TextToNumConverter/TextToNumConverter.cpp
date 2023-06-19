// TextToNumConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

//#include "Converter.cpp"
#include <iostream>

#include "../StringViewExtension.cpp"
#include <string>

int main()
{
    std::wstring_view str = L"- 234 ";

    int ans = strToNum(str);
    //int ans2 = strToNum(str, 16);
    double ans3 = strToFloat<double>(str);


    std::cout << std::endl;
    //convertToNum(L"../dbExample.asm");
}