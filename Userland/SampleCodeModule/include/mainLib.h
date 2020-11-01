#ifndef MAIN_LIB_H
#define MAIN_LIB_H


int writer(int fd, char* buffer, int length);
int reader(int fd, char *buffer, int length);
void scClear();
void chFont(int color);
int timeInfo(int selector);
int memInfo(char *buffer, int address, int bytes);
int regInfo(long int *buffer);

#endif