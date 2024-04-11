#ifndef STDMEMORY_H
#define STDMEMORY_H

#include <libc/stdint.h>

void *memcopy(void *target, const void *source, size_t n);

void *memset(void *string, int c, size_t n);

#endif // STDMEMORY_H