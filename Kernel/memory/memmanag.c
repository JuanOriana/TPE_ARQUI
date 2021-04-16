#define NALLOC 1024
#define MEMORY_CAPACITY 16*1024 + 1
#define NULL 0
#include "memmanag.h"

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

Header *morecoreCust(unsigned);
char *sbrkCust(int size);


static Header base;
static Header *freep = NULL;


// Ref for malloc/free : The C Programming Language  - K&R
void *mallocCust(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecoreCust(nunits)) == NULL)
                return NULL;
    }
}

Header *morecoreCust(unsigned nu)
{
    char *cp;
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrkCust(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    freeCust((void *)(up + 1));
    return freep;
}

void freeCust(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;

    freep = p;
}

// https://codereview.stackexchange.com/questions/226231/implementing-sbrk-for-a-custom-allocator-in-c
char *sbrkCust(int increment)
{
    static char global_mem[MEMORY_CAPACITY] = {0};
    static char *p_break = global_mem;

    char *const limit = global_mem + MEMORY_CAPACITY;
    char *const original = p_break;

    if (increment < global_mem - p_break || increment >= limit - p_break)
    {
        return (char *)-1;
    }
    p_break += increment;

    return original;
}