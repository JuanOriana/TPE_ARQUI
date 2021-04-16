// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <mainLib.h>
#include <timeUtils.h>

static int UTC = -3;

int getSeconds(){
    return timeInfo(SEC);
}

int getMinutes()
{
    return timeInfo(MIN);
}

int getHours(){
    return (timeInfo(HOUR) + UTC + 24 )%24;
}

int getDays()
{
    return timeInfo(DAY);
}

int getMonth()
{
    return timeInfo(MONTH);
}
int getYear()
{
    return timeInfo(YEAR);
}

//Tiempo actual normalizado a segundos desde el iniico del dia
long int getNormSecsInDay(){
    return getSeconds()+getMinutes()*60+ getHours()*3600+getDays();
}

//Espera unos segs determinados
//IMPLEMENTACION RUDIMENTARIA
void hold(int secs){
    long int initTime,currTime;
    int passedDays =0;
    initTime = currTime = getNormSecsInDay();
    while(1){
        long int timeDif=0;
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

void setUTC(int newUTC)
{
    if (newUTC >= -12 && newUTC <= 12)
        UTC = newUTC;
}