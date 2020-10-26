#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

uint64_t sys_register(uint64_t rsi, uint64_t rdx, uint64_t r10);
uint64_t sys_write(uint64_t fd, const uint64_t buffer, uint64_t length);
// uint64_t sys_read(uint64_t fd, char * buffer, uint64_t length);

#endif