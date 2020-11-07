#include <stdint.h>
#include <idtLoader.h>
#include <kbDriver.h>
#include<lib.h>
#include <timer.h>
#include <syscalls.h>

static void int_20();
static void int_21(uint64_t rsp);


void irqDispatcher(uint64_t irq, uint64_t rsp)
{
	switch(irq){
		case 0 :int_20();break;
		case 1 :
			int_21(rsp);
			break;
	}
}

void int_20(){
	timerCycle();
}
void int_21(uint64_t rsp)
{
	keyboardHandler(rsp);
}
