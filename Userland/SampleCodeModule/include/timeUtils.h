

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#define SEC 0
#define MIN 1
#define HOUR 2
#define DAY 3
#define MONTH 4
#define YEAR 5

int getSeconds();
int getMinutes();
int getHours();
int getDays();
int getMonth();
int getYear();
long int getNormSecsInDay();
void hold(int secs);
#endif