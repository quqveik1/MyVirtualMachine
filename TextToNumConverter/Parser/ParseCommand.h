#pragma once

#include <string>
#include <string_view>

template <typename S>
void splitCommand                (S& fullCommand, S& commandName, S& commandData);
template <typename S>
void splitCommand                (S& fullCommand, int& commandStartPos, int& commandNameLastSym, int& dataFirstSymbol);
template <typename S>
int findFirstNotEmptySymPos      (S& fullCommand, int startPos = 0);
template <typename S>
int findFirstSpacePosAfterCommand(S& fullCommand);
template <typename S>
int findLastLineSymbol           (S& fullCommand);