#pragma once
#include <string>

const int cRegister = 4;

const std::wstring ax_string = L"ax";
const std::wstring bx_string = L"bx";
const std::wstring cx_string = L"cx";
const std::wstring dx_string = L"dx";

const int ax_numeric = 0;
const int bx_numeric = 1;
const int cx_numeric = 2;
const int dx_numeric = 3;

int getNumFromStr(std::wstring_view& str);