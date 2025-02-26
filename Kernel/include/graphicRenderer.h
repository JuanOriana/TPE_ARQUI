#ifndef GRAPHIC_RENDERER_H
#define GRAPHIC_RENDERER_H

#include <stdint.h>

#define BG_COLOR 0x000000

void initRenderer(long int infoLoc);
int getHeight();
int getWidth();
int renderArea(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
int renderPixel(unsigned int x, unsigned int y, unsigned int color);
int renderChar(unsigned char c, unsigned int x, unsigned int y, unsigned int color);
void clearAll();
int scrollUp(int pixels);
int renderFig(int *fig, unsigned int x, unsigned int y, unsigned int color);

#endif