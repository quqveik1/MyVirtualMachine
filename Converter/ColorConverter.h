#pragma once

int convColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha/* = 255*/);

unsigned char deconvColorRed  (int color);
unsigned char deconvColorGreen(int color);
unsigned char deconvColorBlue (int color);
unsigned char deconvColorAlpha(int color);