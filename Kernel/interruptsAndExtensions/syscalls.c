#include <stdint.h>
#include <lib.h>
#include <rtc.h>
#include <screenDriver.h>
#include <syscalls.h>
#include <kbDriver.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define STDOUT_COL 0xFFFFFF
#define STDERR_COL 0xFF0000
static int fontColour = STDOUT_COL;

static const char *registers[] = {"RAX:", "RBX:", "RCX:", "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};

uint64_t sysPrintReg(uint64_t rsi, uint64_t rdx, uint64_t rcx)
{
    for (int i = 0; i < 15; i++) {
        char buffer[19] = {'0'};
        sysWrite(STDOUT, (uint64_t) registers[i], 4);
        intToHexa(_getReg(i), buffer, 8);
        sysWrite(STDOUT, (uint64_t) buffer, 19);
        putChar('\n', fontColour);
    }
    return 0;
}

uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length)
{
    char* buff = (char*) buffer;
    unsigned int color;

    switch (fd)
    {
    case STDOUT:
        color= fontColour;
        break;
    case STDERR:
        color = STDERR_COL;
        break;
    default:
        return-1;
    }

    int inserted = 0;
    while (length > 0)
    {
        if (*buff == '\0' || *buff==-1)
            break;
        putChar(*buff, color);
        buff++;
        inserted++;
        length--;
    }

    return inserted;
}

uint64_t sysFig(uint64_t fd, uint64_t fig, uint64_t rcx)
{
    int *figure = (int *)fig;
    unsigned int color;

    switch (fd)
    {
    case STDOUT:
        color = fontColour;
        break;
    case STDERR:
        color = STDERR_COL;
        break;
    default:
        return -1;
    }

    return putFig(figure,color);
}
uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx)
{
    cleanScreen();
    return 0;
}

uint64_t sysFontColour(uint64_t fc, uint64_t rdx, uint64_t rcx)
{
    if(fc == STDERR_COL) { return 1;}
    fontColour = fc;
    return 0;
}

uint64_t sysTime(uint64_t selector, uint64_t rdx, uint64_t rcx)
{
    return getTime(selector);
}

uint64_t sysPrintMem(uint64_t address, uint64_t bytes, uint64_t rcx)
{
    for (int i = 1; i <= bytes; i++, address++) {
        char buffer[5] = {'0'};
        intToHexa(_getMem(address), buffer, 1);
        sysWrite(STDOUT, (uint64_t) buffer, 5);
        putChar('\n', fontColour);
    }
    return 0;
}

uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length)
{
    if (fd != STDIN) {
        return -1;
    }
    char* buff = (char *) buffer;
    return dumpBuffer(buff,length);

}
