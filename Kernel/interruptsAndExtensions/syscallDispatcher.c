#include <stdint.h>
#include <syscalls.h>
#include <syscallDispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t rcx) = {
    sysRead,       //0
    sysWrite,      //1
    sysClear,      //2
    sysFontColour, //3
    sysGetMem,   //4
    sysGetReg,   //5
    sysTime        //6
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx)
{
    return (*systemCalls[rdi])(rsi, rdx, rcx);
}