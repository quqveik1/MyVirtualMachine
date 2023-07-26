//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <exception>

#include "Processor.h"

void readByteCode(std::string path);
long fileSize(FILE* File);
int compiledFileWork(std::string& path, Processor& processor);
void readAndExecuteCommands(Processor& processor);
int executeCommand(Processor& processor);

void endProgramWithCode(int code, Processor& data);