#include <stdint.h>
#include <idtLoader.h>
#include <kbDriver.h>
#include<lib.h>
#include <timer.h>
#include <syscalls.h>

static void int_20();
static void int_21();

static void (*hwInterrupts[])() = {
	int_20,int_21
	};

void irqDispatcher(uint64_t irq) {
	(*hwInterrupts[irq])();
}

void int_20(){
	timerCycle();
}
void int_21(){
	keyboardHandler();
}
