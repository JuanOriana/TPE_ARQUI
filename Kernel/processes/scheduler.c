#include "process.h"
#include "scheduler.h"
#include "interrupts.h"

#define NULL 0

void initScheduler();
static t_pNode *dequeueProcess();
static void enqueueProcess(t_pNode *newProcess);

static t_pList *processes;
static t_pNode *currentProcess;
static t_pNode *idleProcess;
static uint64_t currentProcessTicksLeft;

void idleFunction()
{
      while (1)
      {
            _hlt();
      }
}

void initScheduler()
{
      processes = mallocCust(sizeof(t_pList));
      processes->first = NULL;
      processes->last = processes->first;
      processes->size = 0;
      processes->readyProcesses = 0;
      char *argv[] = {"System Idle Process"};
      initProcess((uint64_t)&idleFunction, 1, argv, 1, 1);
      idleProcess = dequeueProcess();
}

uint64_t scheduler(uint64_t rsp)
{
      if (currentProcess != NULL)
      {
            if (currentProcess->state == READY && currentProcessTicksLeft > 0)
            {
                  currentProcessTicksLeft--;
                  return rsp;
            }

            currentProcess->pcb->rsp = rsp;

            if (currentProcess != idleProcess)
            {

                  enqueueProcess(currentProcess);
            }
            if (processes->readyProcesses > 0)
            {
                  currentProcess = dequeueProcess();

                  while (currentProcess->state != READY)
                  {
                        enqueueProcess(currentProcess);
                        currentProcess = dequeueProcess();
                  }
            }
      }
      else
      {
            currentProcess = idleProcess;
      }

      currentProcessTicksLeft = currentProcess->pcb->priority;
      return currentProcess->pcb->rsp;
}

//t_pNode TIENE UN PUNTERO A PCB NO UN PCB

int addProcess(t_PCB *process)
{
      t_pNode *auxNode = mallocCust(sizeof(t_pNode));
      if (auxNode == NULL)
            return -1;
      auxNode->pcb = process;
      auxNode->state = READY;
      auxNode->next = NULL;
      enqueueProcess(auxNode);
      processes->readyProcesses++;
      processes->size++;
      return 0;
}

int killProcess(uint64_t pid)
{
      changeState(pid, KILLED);
      intTtick();
      return 0;
}

int changeState(uint64_t pid, int state)
{
      t_pNode *auxNode = findProcess(pid);
      if (auxNode == NULL)
            return -1;
      auxNode->state = state;
      return 0;
}

t_pNode *findProcess(uint64_t pid)
{
      for (t_pNode *auxNode = processes->first; auxNode != NULL; auxNode = auxNode->next)
      {

            if (auxNode->pcb->pid == pid)
                  return auxNode;
      }
      return NULL;
}

static t_pNode *dequeueProcess()
{
      if (processes->size == 0)
            return NULL;

      t_pNode *p = processes->first;
      processes->first = processes->first->next;
      processes->size--;

      if (p->state == READY)
            processes->readyProcesses--;

      return p;
}
static void enqueueProcess(t_pNode *newProcess)
{
      if (processes->size == 0)
      {
            processes->first = newProcess;
            processes->last = processes->first;
      }
      else
      {
            processes->last->next = newProcess;
            newProcess->next = NULL;
            processes->last = newProcess;
      }

      if (newProcess->state == READY)
      {
            processes->readyProcesses++;
      }

      processes->size++;
}

int getCurrentPid()
{
      return currentProcess->pcb->pid;
}

t_PCB *getCurrentProcess()
{
      return currentProcess->pcb;
}