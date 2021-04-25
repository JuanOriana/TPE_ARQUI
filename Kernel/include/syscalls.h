#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

uint64_t sysGetReg(uint64_t buffer, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9);
uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysFontColour(uint64_t fc, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysGetMem(uint64_t buffer, uint64_t address, uint64_t bytes, uint64_t r8, uint64_t r9);
uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9);
uint64_t sysTime(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysFig(uint64_t fd, uint64_t fig, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysWriteAtPos(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t x, uint64_t y);
uint64_t sysTimer(uint64_t flag, uint64_t secInt, uint64_t func, uint64_t r8, uint64_t r9);
uint64_t keyBind(uint64_t flag, uint64_t key, uint64_t func, uint64_t r8, uint64_t r9);
uint64_t sysMalloc(uint64_t bytes, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysFree(uint64_t memDirec, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t *getRegs();

#endif