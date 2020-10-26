#include <stdint.h>
#include <lib.h>
#include <screenDriver.h>

#define STDOUT 0
#define STDIN 1
#define STDERR 2

uint64_t sys_register(uint64_t reg, uint64_t rdx, uint64_t r10) {
    return _getReg(reg);
}

uint64_t sys_write(uint64_t fd, uint64_t buffer, uint64_t length)
{
    char* buff = (char*)buffer;
    switch (fd)
    {
    case STDOUT:
        while (length > 0) {
            if (*buff != '\0')
            {
                putChar(*buff, 0xFFFFFF);
            }
            buff++;
            length--;
        }
        break;
    case STDERR:
        while (length > 0) {
            if (*buff != '\0')
            {
                putChar(*buff, 0xFF0000);
            }
            buff++;
            length--;
        }
        break;
    default:
        return-1;
    }
    return 1;
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
//     return 1;
// }
