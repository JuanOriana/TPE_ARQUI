#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);
void intToStr(char *buff, int n);
int _inRead(int n);
uint64_t _getReg(uint64_t reg);
char* intToBase(long int num, char* str, int base);

#endif