#ifndef STRING_H
#define STRING_H

#pragma once

#include <libc/stdint.h>
#include <screen.h>

// Length of a string
size_t strlen(char *str);

// Determine buffer length
int string_length(uint8_t *string);

// Print text
void print(const char *string);

#endif // STRING_H