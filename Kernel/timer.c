// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <timer.h>
long int timeStep = 0;
int timerEnabled=0;
int secInterval=0;
void (*function)();

int timerEnable(int secInt, functiontype f){
    int flag=0;
    if (timerEnabled) flag=1;
    function=f;
    secInterval=secInt;
    timeStep=0;
    timerEnabled=1;
    return flag;
}

void timerCycle(){
    if (timerEnabled){
        timeStep+=55;
        if (timeStep/1000>=secInterval){
            timeStep = timeStep % 1000;
            function();
        }
    }

}

void timerStop(){
    timeStep=timerEnabled=0;
}