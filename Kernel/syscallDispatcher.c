#include <stdint.h>
#include <syscalls.h>
#include <syscallDispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t r10) = {
    sysPrintReg, //0
    sys_write,    //1
    // sys_read
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10)
{
    return (*systemCalls[rdi])(rsi, rdx, r10);
}