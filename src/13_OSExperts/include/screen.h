#ifndef SCREEN_H
#define SCREEN_H

#include <libc/stdint.h>
#include <libc/stdmemory.h>
#include <libc/global.h>
#include <libc/string.h>

void init_screen(void);

void clear(void);

void scroll(void);

void cursor_blinker(void);

void set_text_color(uint8_t background_color, uint8_t foreground_color);

void putchar(uint8_t ic);

void putstring(uint8_t *string);

#endif // SCREEN_H