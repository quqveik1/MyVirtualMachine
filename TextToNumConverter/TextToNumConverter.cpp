// TextToNumConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include "Converter.cpp"
/*

int fib(int n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;

    return fib(n - 1) + fib(n - 2);
}
*/

int main()
{
    convertToNum(L"../AsmCode/Factorial.asm");
}