#include <stdint.h>
#include <syscalls.h>
#include <syscall_dispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) = {
    sys_register
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
    return (*systemCalls[rdi])(rsi, rdx, r10, r9, r8);
}