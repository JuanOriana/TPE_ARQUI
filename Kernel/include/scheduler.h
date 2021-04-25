#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include "process.h"
#include <interrupts.h>

typedef enum { READY,
               BLOCKED,
               KILLED }
t_state;

typedef struct t_pNode {
      t_PCB* pcb;
      t_state state;
      struct t_pNode* next;
} t_pNode;


typedef struct pList {
      uint32_t size;
      uint32_t readyProcesses;
      t_pNode* first;
      t_pNode* last;
} t_pList;


int getCurrentPid();
t_pNode *findProcess(uint64_t pid);
int changeState(uint64_t pid, int state);
t_PCB* getCurrentProcess();

//getCurrentProcess
//addProcess

#endif