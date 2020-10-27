#include <stdint.h>
#include <lib.h>
#include <screenDriver.h>

#define STDOUT 0
#define STDIN 1
#define STDERR 2

#define STDOUT_COL 0xFFFFFF
#define STDERR_COL 0xFF0000

uint64_t sys_register(uint64_t reg, uint64_t rdx, uint64_t r10) {
    return _getReg(reg);
}

uint64_t sys_write(uint64_t fd, uint64_t buffer, uint64_t length)
{
    char* buff = (char*)buffer;
    unsigned int color;

    switch (fd)
    {
    case STDOUT:
        color= STDOUT_COL;
        break;
    case STDERR:
        color = STDERR_COL;
        break;
    default:
        return-1;
    }

    while (length > 0)
    {
        if (*buff != '\0')
        {
            putChar(*buff, color);
        }
        buff++;
        length--;
    }

    return 0;
}

// uint64_t sys_read(uint64_t fd, char * buffer, uint64_t length) {
//     if (fd != STDIN) {
//         return -1;
//     }
//     while (length > 0) {
//         *buffer = kbFlag();
//         buffer++;
//         length--;
//     }
//     return 0;
// }
