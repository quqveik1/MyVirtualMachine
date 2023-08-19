#pragma once

#include <string>

//extension without dot
template<typename STR>
int deleteExtension(STR& fileName);
//extension without dot
template<typename STR>
int changeExtension(STR& fileName, STR newExtension);