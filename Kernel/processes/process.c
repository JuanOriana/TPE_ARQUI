#include "process.h"
#include "scheduler.h"

uint64_t pid = 0;

long initProcess(uint64_t entryPoint, int argc, char** argv, uint8_t fg) {
    if (entryPoint == NULL) return -1;

    t_PCB * process;
    if ((process = mallocCust(sizeof(t_PCB))) == NULL) return -1;

    strcpy(process->name, argv[0]);

    if (pid != 0) {
        process->ppid = getCurrentPid();
    }
    else {
        process->ppid = -1;
    }
    process->pid = pid;
    process->fg = fg;
    if (pid == 0) {
        for (int i = 0; i < MAX_FD; i++) {
            process->fd[i] = -1;
        }
        process->fd[0] = STDIN;
        process->fd[1] = STDOUT;
        process->fd[2] = STDERR;
    }
    else {
        t_PCB * currProc = getCurrentProcess();
        for (int i = 0; i < MAX_FD; i++) {
            process->fd[i] = currProc->fd[i];
        }
    }

    if( (process->stackBase = mallocCust(SIZE_OF_STACK)) == NULL) {
        freeCust((void *)process);
        return -1;
    }
    process->rbp = process->stackBase + SIZE_OF_STACK - 16;
    process->rsp = process->rbp - sizeof(t_stackFrame);
    initStackFrame(entryPoint, argc, argv, process->rbp);

    addProcess(process);

    return pid++;
}

void initStackFrame(uint64_t entryPoint, int argc, char** argv, uint64_t rbp) {
    t_stackFrame * frame = (t_stackFrame*) rbp;
    frame->r15 = 0x001;
    frame->r14 = 0x002;
    frame->r13 = 0x003;
    frame->r12 = 0x004;
    frame->r11 = 0x005;
    frame->r10 = 0x006;
    frame->r9 = 0x007;
    frame->r8 = 0x008;
    frame->rsi = (uint64_t)argc;
    frame->rdi = (uint64_t)entryPoint;
    frame->rbp = rbp;
    frame->rdx = (uint64_t)argv;
    frame->rcx = 0x009;
    frame->rbx = 0x00A;
    frame->rax = 0x00B;
    frame->rip = (uint64_t)wrapper;
    frame->cs = 0x008;
    frame->rflags = 0x202;
    frame->rsp = rbp;
    frame->ss = 0x000;
}

void wrapper(void (*entryPoint)(int, char**), int argc, char** argv) {
      entryPoint(argc, argv);
      exit();
}