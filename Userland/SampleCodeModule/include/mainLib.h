#ifndef MAIN_LIB_H
#define MAIN_LIB_H


void intToStr(char* buff, int n);
int write(int fd, char* buffer, int length);
int read(int fd, char *buffer, int length);
void scClear();
void chFont(int color);
int timeInfo(int selector);

#endif