#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
void initVideo(long int infoLoc);
int renderPixel(unsigned int x, unsigned int y, unsigned int color);
int renderChar(unsigned char c, unsigned int x, unsigned int y, unsigned int color);

#endif