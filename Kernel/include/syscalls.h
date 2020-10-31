#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

uint64_t sysPrintReg(uint64_t rsi, uint64_t rdx, uint64_t rcx);
uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length);
uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx);
uint64_t sysFontColour(uint64_t fc, uint64_t rdx, uint64_t rcx);
uint64_t sysPrintMem(uint64_t address, uint64_t bytes, uint64_t rcx);
uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length);
uint64_t sysTime(uint64_t rsi, uint64_t rdx, uint64_t rcx);

#endif