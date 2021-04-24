// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <syscalls.h>
#include <syscallDispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) = {
    sysRead,       //0
    sysWrite,      //1
    sysClear,      //2
    sysFontColour, //3
    sysGetMem,     //4
    sysGetReg,     //5
    sysTime,       //6
    sysFig,        //7
    sysWriteAtPos, //8
    sysTimer,      //9
    keyBind,       //10
    sysMalloc,     //11
    sysFree,       //12
    sysMMDump      //13
};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return (*systemCalls[rdi])(rsi, rdx, rcx, r8, r9);
}