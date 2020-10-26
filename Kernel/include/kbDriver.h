#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H
#include <defs.h>

#define BUFFER_SIZE 128
void initKb();
int getChar();
void keyboardHandler();

#endif 