#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <isr.h>

void keyboard_handler(registers_t * r);

void keyboard_init();

#endif