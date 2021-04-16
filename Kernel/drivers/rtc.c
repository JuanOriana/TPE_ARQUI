// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

long int getNormSecsInDay(){
    return getTime(0)+getTime(1)*60+ getTime(2)*3600+getTime(3);
}

//Espera unos segs determinados
//IMPLEMENTACION RUDIMENTARIA
void hold(int secs){
    long int initTime,currTime;
    long int timeDif=0;
    int passedDays =0;
    initTime = currTime = getNormSecsInDay();
    while(1){
        currTime = getNormSecsInDay();
        timeDif = currTime - initTime + (passedDays * 86400);
        if (timeDif<0){ //Paso un dia
            passedDays++;
            timeDif+=86400;
        }

        if (timeDif>=secs)
            return;

    }
}
