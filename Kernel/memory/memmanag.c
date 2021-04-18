// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "memmanag.h"
#define MEMORY_CAPACITY 0x8000000
#define GLOBAL_MEM (char *)(0x600000)
#define LIMIT GLOBAL_MEM + MEMORY_CAPACITY
#define NALLOC 1024
#define NULL 0

typedef long Align;
typedef union header Header;

union header
{
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

Header *morecoreCust(unsigned long);
char *sbrkCust(unsigned long);

static Header base;
static Header *freep = NULL;

// Ref for malloc/free : The C Programming Language  - K&R
void *mallocCust(unsigned long nbytes)
{
    Header *p, *prevp;
    unsigned long nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; //Normalize to header units

    if ((prevp = freep) == NULL) //Init ptr on first malloc
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits) //If >=, can use this block
        {
            if (p->s.size == nunits) // Equal just use
                prevp->s.ptr = p->s.ptr;
            else // Fragment block
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1); //Return new memspace WITHOUT header
        }
        if (p == freep) // No block found, need more space
            if ((p = morecoreCust(nunits)) == NULL)
                return NULL;
    }
}

Header *morecoreCust(unsigned long nunits)
{
    char *newMem;
    Header *memToHeader;
    if (nunits < NALLOC)
        nunits = NALLOC;
    newMem = sbrkCust(nunits * sizeof(Header));
    if (newMem == (char *)-1)
        return NULL;
    memToHeader = (Header *)newMem;
    memToHeader->s.size = nunits;
    freeCust((void *)(memToHeader + 1));
    return freep;
}

void freeCust(void *freeMem)
{
    Header *freeBlock, *p;

    freeBlock = (Header *)freeMem - 1;                                      //Add header to mem to free
    for (p = freep; !(freeBlock > p && freeBlock < p->s.ptr); p = p->s.ptr) // Find blocks that surround
        if (p >= p->s.ptr && (freeBlock > p || freeBlock < p->s.ptr))       //Free block might be on the ends
            break;

    if (freeBlock + freeBlock->s.size == p->s.ptr) //Join right
    {
        freeBlock->s.size += p->s.ptr->s.size;
        freeBlock->s.ptr = p->s.ptr->s.ptr;
    }
    else
        freeBlock->s.ptr = p->s.ptr;

    if (p + p->s.size == freeBlock) //Join left
    {
        p->s.size += freeBlock->s.size;
        p->s.ptr = freeBlock->s.ptr;
    }
    else
        p->s.ptr = freeBlock;

    freep = p;
}

// https://codereview.stackexchange.com/questions/226231/implementing-sbrk-for-a-custom-allocator-in-c
char *sbrkCust(unsigned long increment)
{
    static char *pBreak = GLOBAL_MEM;
    char *const original = pBreak;

    if (increment < GLOBAL_MEM - pBreak || increment >= LIMIT - pBreak)
    {
        return (char *)-1;
    }
    pBreak += increment;

    return original;
}