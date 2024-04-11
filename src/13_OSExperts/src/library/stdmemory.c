#include <libc/stdmemory.h>

void *memcopy(void *target, const void *source, size_t n) {
    size_t i;
    
    for(i = 0; i < n; i++) {
        ((uint16_t *) target)[i] = ((uint16_t *) source)[i];
    }

    return target;
}

void *memset(void *string, int c, size_t n) {
    size_t i;

    for(i = 0; i < n; i++) {
        ((uint16_t *) string)[i] = c;
    }

    return string;
}