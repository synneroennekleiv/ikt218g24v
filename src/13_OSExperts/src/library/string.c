#include <libc/string.h>

int string_length(uint8_t *string) {
    int i;

    for(i = 0; *string; string++) {
        i++;
    }

    return i;
}

void print(const char *string) {
    while (*string != '\0') {
        putchar((uint8_t)*string);
        string++;
    }
}
