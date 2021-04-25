// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <lib.h>
#include <rtc.h>
#include <screenDriver.h>
#include <syscalls.h>
#include <kbDriver.h>
#include <font.h>
#include <timer.h>
#include <stdint.h>
#include <memmanag.h>

#define STDOUT_COL 0xFFFFFF
#define STDERR_COL 0xFF0000
static int fontColour = STDOUT_COL;

// static const char *registers[] = {"RAX:", "RBX:", "RCX:", "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};
static uint64_t regs[17] = {0};

uint64_t *getRegs()
{
    return regs;
}
uint64_t sysGetReg(uint64_t buffer, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    long long *array = (long long *)buffer;
    for (int i = 0; i < 15; i++)
    {
        array[i] = regs[i];
    }
    return 0;
}

uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    char *buff = (char *)buffer;
    unsigned int color;

    switch (fd)
    {
    case STDOUT:
        color = fontColour;
        break;
    case STDERR:
        color = STDERR_COL;
        break;
    case STDIN:
        break;
    default:
        return -1;
    }

    int inserted = 0;
    while (length > 0)
    {
        if (*buff == '\0' || *buff == -1)
            break;
        if (fd == STDIN)
            loadChar(*buff);
        else
            putChar(*buff, color);
        buff++;
        inserted++;
        length--;
    }

    return inserted;
}

uint64_t sysFig(uint64_t fd, uint64_t fig, uint64_t rcx, uint64_t r8, uint64_t r9)
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

    return putFig(figure, color);
}
uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    cleanScreen();
    return 0;
}

uint64_t sysFontColour(uint64_t fc, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    if (fc == STDERR_COL)
    {
        return 1;
    }
    fontColour = fc;
    return 0;
}

uint64_t sysTime(uint64_t selector, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return getTime(selector);
}

uint64_t sysGetMem(uint64_t buffer, uint64_t address, uint64_t bytes, uint64_t r8, uint64_t r9)
{
    unsigned char *array = (unsigned char *)buffer;
    for (unsigned char i = 0; i < bytes; i++)
    {
        array[i] = (unsigned char)_getMem(address + i);
    }
    return 0;
}

uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    if (fd != STDIN)
    {
        return -1;
    }
    char *buff = (char *)buffer;
    return dumpBuffer(buff, length);
}

uint64_t sysWriteAtPos(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t x, uint64_t y)
{
    char *buff = (char *)buffer;
    if (fd != STDOUT)
        return -1;
    int inserted = 0;
    for (int i = 0; i < length; i++)
    {
        if (*buff == '\0' || *buff == -1)
            break;
        putCharAtPos(*buff, fontColour, x + i * ABS_WIDTH, y); //Y si me pase de linea? Mala suerte! No se imprime
        buff++;
        inserted++;
    }
    return inserted;
}

uint64_t sysTimer(uint64_t flag, uint64_t secInt, uint64_t func, uint64_t r8, uint64_t r9)
{
    if (!flag) //flag = 0 es un stop!
    {
        timerStop();
        return 0;
    }
    return timerEnable(secInt, (functiontype)func);
}

uint64_t keyBind(uint64_t flag, uint64_t key, uint64_t func, uint64_t r8, uint64_t r9)
{
    if (!flag) //flag = 0 es un Unbind!
    {
        return cleanKeyFun(key);
    }
    return setKeyFun(key, (functiontype)func);
}

uint64_t sysMalloc(uint64_t bytes, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return (uint64_t)mallocCust(bytes);
}

uint64_t sysFree(uint64_t memDirec, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    freeCust((void *)memDirec);
    return 0;
}