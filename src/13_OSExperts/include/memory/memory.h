// memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <libc/stdint.h> // for size_t

void *memset(void *s, int c, size_t n);

void malloc();

void free();

//void init_kernel_memory(&end);

void init_paging();

void print_memory_layout();



#endif // MEMORY_H