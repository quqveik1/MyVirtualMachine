//
// Created by Kurlic on 04.05.2023.
//
#pragma once

void initCommandsArr();
void readByteCode(std::wstring path);
void readAndExecuteCommands(std::wstring_view& text);
int executeCommand(std::wstring_view& command);
int findFirstSpacePos(std::wstring_view& fullCommand);
void splitCommand(std::wstring_view& fullCommand, std::wstring_view& commandName, std::wstring_view& commandData);
int callCommandByName(std::wstring_view& commandName, std::wstring_view& commandData);

void endProgramWithCode(int code, int lastLine, std::wstring_view& lastStr);