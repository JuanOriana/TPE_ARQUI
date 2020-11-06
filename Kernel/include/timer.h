#ifndef TIMER_H
#define TIMER_H

typedef void (*functiontype)();

int timerEnable(int secInt, functiontype f);
void timerCycle();
void timerStop();



#endif