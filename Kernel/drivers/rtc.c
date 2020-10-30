#include <rtc.h>

int getTime(unsigned int selector){
    switch (selector)
    {
    case SEC:
        return _RTC(GET_SEC);
    case MIN:
        return  _RTC(GET_MIN);
    case HOUR:
        return _RTC(GET_HOUR);
    case DAY:
        return _RTC(GET_DAY);
    case MONTH:
        return _RTC(GET_MONTH);
    case YEAR:
        return _RTC(GET_YEAR);
    default:
        return -1;
    }
}