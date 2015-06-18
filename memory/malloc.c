#include "malloc.h"

inline void* End(Header *H)
{
    return H->data + H->size;
}

void* AlignmentFill(void* p)
{
    long isAligned = (long)p & 8;

    if (isAligned != 0 && isAligned != 8)
        return p + 8 - isAligned;
    else
        return p;
}

void free(void* pointer)
{
    Header* H = (Header*)(pointer - sizeof(Header));
    H->prev->next = H->next;
    H->next->prev = H->prev;
}

Header* MakeReal(Header *V, Header *H)
{
    Header *newV = (Header*)AlignmentFill(End(H));

    newV->size = V->size;
    newV->next = V->next;
    newV->prev = V->prev;
    newV->data = V->data;

    return newV;
}

void* malloc(unsigned int size)
{
    int allocated = 0;
    Header tmp;
    Header *V = &tmp;
    Header *H = &_heap_start;

    if (H->data == (void*)0)
        H->data = sizeof(Header) + &_heap_start;

//	Header *_heap_end = (Header*)_heap_start + 100;
    V->size = size;

    while (allocated == 0)
    {
        V->prev = H->prev;
        V->next = H->next;
        V->data = sizeof(Header) + AlignmentFill(End(H));

        if (V->next == 0)
        {
            if (End(V) < (void*)&_heap_end) // if the new allocation fits between the current and the memory limit
            {
                V = MakeReal(V, H); // makes V real
                allocated = 1;		// signal to quit loop
                if(V != H)			// possibly redundant?
                {
                    H->next = V;	// updates pointers
                    V->prev = H;
                    V->next = 0;
                }
            }
//            else ERROR
        }
        else if (End(V) <= (void*)V->next) // fits between H_j and H_j+1
        {
            allocated = 1;		// signal to quit loop
            V = MakeReal(V, H);	// makes V real
            V->next = H->next;	// updates pointers
            V->prev = H;
            H->next->prev = V;
            H->next = V;
        }
        H = H->next;				// H_j -> H_j+1
    }

    return V->data;
}
