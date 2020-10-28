#include <stdint.h>
#include <syscalls.h>
#include <syscallDispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t r10) = {
    sysPrintReg, //0
    sysWrite,    //1
    // sys_read
    sysClear,  //3
    sysFontColour,//4
    sysTime
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10)
{
    return (*systemCalls[rdi])(rsi, rdx, r10);
}