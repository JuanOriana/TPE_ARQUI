#ifndef _MEMMANAG_H

void *mallocCust(unsigned long nbytes);
void freeCust(void *ap);
void dumpMM(long* baseRet, long* freeMem, long* totalMem);

#endif
