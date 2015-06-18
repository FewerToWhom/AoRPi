#ifndef MALLOC_H
#define MALLOC_H

#define NULL 0

typedef struct Header Header;

struct Header {
    unsigned int size;
    Header* prev;
    Header* next;
    void* data;
};

extern Header _heap_start;
extern Header _heap_end;

void* malloc(unsigned int size);
void free(void* pointer);

#endif
