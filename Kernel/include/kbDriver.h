#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H
#include <defs.h>
#include <stdint.h>
#define BUFF_SIZE 256
void initKb();
void keyboardHandler(uint64_t rsp);
void loadChar(char c);
int dumpChar();
// devuelve cuantos chars se pudieron dumpear
int dumpBuffer(char *destination, int size);
void loadRegs(uint64_t *rsp);
#endif 