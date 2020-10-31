#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H
#include <defs.h>

#define BUFF_SIZE 256
void initKb();
void keyboardHandler();
int loadChar();
// devuelve cuantos chars se pudieron dumpear
int dumpBuffer(char *destination, int size);

#endif 