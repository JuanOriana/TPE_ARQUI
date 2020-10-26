#include <stdint.h>
#include <syscalls.h>
#include <syscallDispatcher.h>

static uint64_t (*systemCalls[])(void * rsi, void * rdx, void * r10) = {
    sys_register, //0
    sys_write,     //1
    // sys_read
};

uint64_t syscallDispatcher(uint64_t rdi, void * rsi, void * rdx, void * r10) {
    return (*systemCalls[rdi])(rsi, rdx, r10);
}