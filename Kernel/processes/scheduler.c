#include "process.h"
#include "scheduler.h"

void initScheduler();

static t_pList* processes;

void initScheduler() {
      processes = mallocCust(sizeof(t_pList));
      processes->first = NULL;
      processes->last = processes->first;
      processes->size = 0;
      processes->readyProcesses = 0;
}