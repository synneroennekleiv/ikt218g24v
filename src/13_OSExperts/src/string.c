#include <libc/string.h>


size_t strlen(const char* str)
 {
    int i;

    for(i = 0; *str; str++) {
        i++;
    }

    return i;
}