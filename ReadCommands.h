//
// Created by Kurlic on 04.05.2023.
//
#pragma once

#include <exception>

#include "Processor/Processor.h"

ErrorCode readByteCode(std::string path);
long fileSize(FILE* File);