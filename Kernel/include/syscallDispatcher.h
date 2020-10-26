#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H

#include <stdint.h>

uint64_t syscallDispatcher(uint64_t rdi, void * rsi, void * rdx, void * r10);

#endif