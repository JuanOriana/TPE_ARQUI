#ifndef MAIN_LIB_H
#define MAIN_LIB_H

#define TIMER_STOP 0
#define TIMER_START 1

int writer(int fd, char *buffer, int length);
int reader(int fd, char *buffer, int length);
void scClear();
void chFont(long int color);
int timeInfo(int selector);
int drawFig(int fd, int *fig);
int getMem(unsigned char *buff, unsigned long long address, int bytes);
int getRegs(unsigned long long *arr);
int writeAtPos(int fd, char *buffer, int length, int x, int y);
int timer(int flag, int secInt, void (*f)());
int keyBinder(int flag, int key, void (*f)());
void opCodeExc(void);
void *pureMalloc(unsigned long nbytes);
void pureFree(void *memDirec);
#endif