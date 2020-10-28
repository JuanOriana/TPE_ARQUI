#define GET_SEC 0x00
#define GET_MIN 0x02
#define GET_HOUR 0x04
#define GET_DAY 0x07 //Dia mensual
#define GET_MONTH 0x08
#define GET_YEAR 0x09

#define SEC 0
#define MIN 1
#define HOUR 2
#define DAY 3
#define MONTH 4
#define YEAR 5

int _RTC(unsigned int rtcSelector);
int getTime(unsigned int timeSelector);


