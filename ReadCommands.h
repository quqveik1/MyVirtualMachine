//
// Created by Kurlic on 04.05.2023.
//
#pragma once

void readByteCode();
void readAndExecuteCommands(std::string_view& text);
int executeCommand(std::string_view& command);
int findFirstSpacePos(std::string_view& fullCommand);
void splitCommand(std::string_view& fullCommand, std::string_view& commandName, std::string_view& commandData);
int callCommandByName(std::string_view& commandName, std::string_view& commandData);