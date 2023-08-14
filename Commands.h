//
// Created by Kurlic on 04.05.2023.
//
#pragma once
#include <string_view>
#include <string>

#include "Constants/CommandConstants.h"
#include "Processor/Processor.h"

using COMMANDTYPE = int (*)(Processor& processor, int codedCommandNum);

int in_command     (Processor& processor, int codedCommandNum);
int out_command    (Processor& processor, int codedCommandNum);

int evalExpression (Processor& processor, int codedCommandNum);
int push_command   (Processor& processor, int codedCommandNum);

int hlt_command    (Processor& processor, int codedCommandNum);

int add_command    (Processor& processor, int codedCommandNum);
int sub_command    (Processor& processor, int codedCommandNum);
int mul_command    (Processor& processor, int codedCommandNum);
int div_command    (Processor& processor, int codedCommandNum);

int pop_command    (Processor& processor, int codedCommandNum);

int doJump         (Processor& processor, int pos);
int commonJmpFnc   (Processor& processor, bool needToJump, int codedNum);
int jmp_command    (Processor& processor, int codedCommandNum);
int get2ElementsFromStack(float* a, float* b, Processor& processor);
int ja_command     (Processor& processor, int codedCommandNum);
int jae_command    (Processor& processor, int codedCommandNum);
int jb_command     (Processor& processor, int codedCommandNum);
int jbe_command    (Processor& processor, int codedCommandNum);
int je_command     (Processor& processor, int codedCommandNum);
int jne_command    (Processor& processor, int codedCommandNum);

int sqrt_command   (Processor& processor, int codedCommandNum);
int sin_command    (Processor& processor, int codedCommandNum);
const int defaultSinLen                            = 8;
double sinus                (double number, int len = defaultSinLen);
unsigned long long factorial(int n);

int call_command   (Processor& processor, int codedCommandNum);
int ret_command    (Processor& processor, int codedCommandNum);

int neg_command    (Processor& processor, int codedCommandNum);

int into_command   (Processor& processor, int codedCommandNum);

int setpxl_command (Processor& processor, int codedCommandNum); 
int si_command     (Processor& processor, int codedCommandNum); 