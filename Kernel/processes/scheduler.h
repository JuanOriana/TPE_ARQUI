#ifndef _SCHEDULER_H

typedef struct t_pNode {
      t_PCB pcb;
      t_state state;
      struct t_pNode* next;
} t_pNode;

typedef struct pList {
      uint32_t size;
      uint32_t readyProcesses;
      t_pNode* first;
      t_pNode* last;
} t_pList;


//getCurrentPid
//getCurrentProcess
//addProcess

#endif