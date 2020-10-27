#include <stdint.h>
#include <lib.h>
#include <screenDriver.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define STDOUT_COL 0xFFFFFF
#define STDERR_COL 0xFF0000

static const char *registers[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};

uint64_t sysPrintReg(uint64_t rsi, uint64_t rdx, uint64_t r10) {
    for (int i = 0; i < 15; i++) {
        char buffer[18] = {'0'};
        for (int j = 0; j < 3; j++){
            putChar(registers[i][j], STDOUT_COL);
        }
        putChar(':', STDOUT_COL);
        intToBase(_getReg(i), buffer, 16);
        for (int j = 0; j < 18; j++) {
            putChar(buffer[j], STDOUT_COL);
        }
        putChar('\n', STDOUT_COL);
    }
    return 0;
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
        if (*buff == '\0' || *buff==-1)
            break;
        putChar(*buff, color);
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
