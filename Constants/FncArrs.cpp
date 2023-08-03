#pragma once

#include "FncArrs.h"

void initCommandsArr()
{
    commandsArr[in_num] = in_command;
    commandsArr[out_num] = out_command;
    commandsArr[push_num] = push_command;
    commandsArr[hlt_num] = hlt_command;
    commandsArr[add_num] = add_command;
    commandsArr[sub_num] = sub_command;
    commandsArr[mul_num] = mul_command;
    commandsArr[div_num] = div_command;
    commandsArr[pop_num] = pop_command;
    commandsArr[jmp_num] = jmp_command;
    commandsArr[ja_num] = ja_command;
    commandsArr[jae_num] = jae_command;
    commandsArr[jb_num] = jb_command;
    commandsArr[jbe_num] = jbe_command;
    commandsArr[je_num] = je_command;
    commandsArr[jne_num] = jne_command;
    commandsArr[sqrt_num] = sqrt_command;

    commandsArr[call_num] = call_command;
    commandsArr[ret_num] = ret_command;

    commandsArr[neg_num] = neg_command;
    commandsArr[imto_num] = imto_command;
    commandsArr[breakpoint_num] = breakpoint_command;

    commandsArr[pixel_num] = pixel_command;
}