#pragma once

#include <libc/stdbool.h>
#include <libc/stdint.h>

#define EOF (-1)

// Print a string of characters
bool print(const char* data, size_t length);

// Print a formatted string
int printf(const char* __restrict__ format, ...);