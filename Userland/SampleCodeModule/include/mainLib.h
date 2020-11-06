#ifndef MAIN_LIB_H
#define MAIN_LIB_H


int writer(int fd, char* buffer, int length);
int reader(int fd, char *buffer, int length);
void scClear();
void chFont(long int color);
int timeInfo(int selector);
int drawFig(int fd, int* fig);
int getMem(unsigned char *buff, unsigned long long address, int bytes);
int getRegs(unsigned long long* arr);
int writeAtPos(int fd, char *buffer, int length,int x, int y);
#endif