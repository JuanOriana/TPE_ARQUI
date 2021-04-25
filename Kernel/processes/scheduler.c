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

// void* scheduler(){
//       pr
//       t_pNode *node = processes->first;
//       while(node->state!=READY)

// }

// int addProcess(t_PCB* process){
//       t_pNode *auxNode = mallocCust(sizeof(t_pNode));
//       if(auxNode == NULL)
//             return -1;
//       if(processes->size == 0)

       
// }