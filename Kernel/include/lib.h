#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);
void intToStr(char *buff, int n);
int _inRead(int n);
uint64_t _getReg(uint64_t reg);
unsigned char _getMem(uint64_t address);

char *reverse(char *buffer, int i, int j);
char *intToHexa(long long num, char *str, int bytes);
void printRegisters(uint64_t rsp);
int abs(int n);
char* strcopy(char* destination, char* source);


#endif