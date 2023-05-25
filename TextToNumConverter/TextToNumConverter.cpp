// TextToNumConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "../../StringSort/WStringFnc.cpp"
#include "../ReadCommands.cpp"

#include "Converter.cpp"

int main()
{
    convertToNum(L"../kvm.bc");
}