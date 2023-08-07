#pragma once

#include "ColorConverter.h"

int convColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 0xFF)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

unsigned char deconvColorRed(int color) 
{
    return (color >> 16) & 0xFF;
}

unsigned char deconvColorGreen(int color)
{
    return (color >> 8) & 0xFF;
}

unsigned char deconvColorBlue(int color)
{
    return color & 0xFF;
}

unsigned char deconvColorAlpha(int color)
{
    return (color >> 24) & 0xFF;
}
