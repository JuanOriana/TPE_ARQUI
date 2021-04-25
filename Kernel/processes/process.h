#ifndef _PROCESS_H

#include <stdint.h>
#include "syscalls.h"
#include "memmanag.h"
#define SIZE_OF_STACK (8 * 1024)
#define MAX_FD 5
#define NULL 0

typedef struct {
      uint64_t r15;
      uint64_t r14;
      uint64_t r13;
      uint64_t r12;
      uint64_t r11;
      uint64_t r10;
      uint64_t r9;
      uint64_t r8;
      uint64_t rsi;
      uint64_t rdi;
      uint64_t rbp;
      uint64_t rdx;
      uint64_t rcx;
      uint64_t rbx;
      uint64_t rax;

      uint64_t rip;
      uint64_t cs;
      uint64_t rflags;
      uint64_t rsp;
      uint64_t ss;
} t_stackFrame;

typedef struct {
      uint64_t pid;
      uint64_t ppid;
      uint64_t priority;
      uint8_t fg;
      uint16_t fd[MAX_FD];
      char name[20];
      uint64_t rsp;
      uint64_t rbp;
      uint64_t stackBase;
} t_PCB;

static long initProcess(uint64_t entryPoint, int argc, char** argv, uint8_t fg);
static void wrapper(void (*entryPoint)(int, char**), int argc, char** argv);
static void freeProcess(t_PCB * process);

#endif