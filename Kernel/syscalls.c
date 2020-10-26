#include <stdint.h>
#include <lib.h>

uint64_t sys_register(uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
    return _getReg(rsi);
}