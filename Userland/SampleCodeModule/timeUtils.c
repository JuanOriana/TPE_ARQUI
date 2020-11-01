
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
    return timeInfo(HOUR) + UTC;
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

void setUTC(int newUTC)
{
    if (newUTC >= -12 || newUTC <= 12)
        UTC = newUTC;
}