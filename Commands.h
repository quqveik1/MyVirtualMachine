//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "Constants/CommandConstants.h"
#include "Processor/Processor.h"

using COMMANDTYPE =
ErrorCode (*)            (Processor& processor, int codedCommandNum);

ErrorCode in_command     (Processor& processor, int codedCommandNum);
ErrorCode out_command    (Processor& processor, int codedCommandNum);

ErrorCode evalExpression (Processor& processor, int codedCommandNum);
ErrorCode push_command   (Processor& processor, int codedCommandNum);

ErrorCode hlt_command    (Processor& processor, int codedCommandNum);

ErrorCode add_command    (Processor& processor, int codedCommandNum);
ErrorCode sub_command    (Processor& processor, int codedCommandNum);
ErrorCode mul_command    (Processor& processor, int codedCommandNum);
ErrorCode div_command    (Processor& processor, int codedCommandNum);

ErrorCode pop_command    (Processor& processor, int codedCommandNum);

ErrorCode doJump         (Processor& processor, CommandDataType pos);
ErrorCode commonJmpFnc   (Processor& processor, bool needToJump, int codedNum);
ErrorCode jmp_command    (Processor& processor, int codedCommandNum);
ErrorCode ja_command     (Processor& processor, int codedCommandNum);
ErrorCode jae_command    (Processor& processor, int codedCommandNum);
ErrorCode jb_command     (Processor& processor, int codedCommandNum);
ErrorCode jbe_command    (Processor& processor, int codedCommandNum);
ErrorCode je_command     (Processor& processor, int codedCommandNum);
ErrorCode jne_command    (Processor& processor, int codedCommandNum);

ErrorCode sqrt_command   (Processor& processor, int codedCommandNum);
ErrorCode sin_command    (Processor& processor, int codedCommandNum);
ErrorCode fmod_command   (Processor& processor, int codedCommandNum);
const int defaultSinLen                            = 8;
double sinus                (double number, int len = defaultSinLen);
unsigned long long factorial(int n);

ErrorCode call_command   (Processor& processor, int codedCommandNum);
ErrorCode ret_command    (Processor& processor, int codedCommandNum);

ErrorCode neg_command    (Processor& processor, int codedCommandNum);

ErrorCode into_command   (Processor& processor, int codedCommandNum);

ErrorCode setpxl_command (Processor& processor, int codedCommandNum);
ErrorCode rdsys_command  (Processor& processor, int codedCommandNum);

ErrorCode wait_command   (Processor& processor, int codedCommandNum);