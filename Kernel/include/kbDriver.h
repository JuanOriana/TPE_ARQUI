#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H
#include <defs.h>

#define BUFF_SIZE 256
void initKb();
void keyboardHandler();
char getChar();
// 0 si se pudo dumpear todo el buffer, -1 en caso contrario.
int dumpBuffer(char *destination, int size);

#endif 