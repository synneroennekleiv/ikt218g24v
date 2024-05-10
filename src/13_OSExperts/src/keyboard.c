#include "libc/stdint.h"
#include "descriptor_tables.h"
#include "util.h"
#include "libc/stdio.h"
#include "keyboard.h"
#include "libc/stdbool.h"
#include <io_ports.h>
#include <isr.h>
#include <monitor.h>
#include <libc/stdbool.h>

// A simple lookup table. You'll likely want to expand this for shifted symbols.
static unsigned char ascii_lookup_table[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t input_buffer_occupancy = 0;
char input_buffer[256];
bool caps_lock_active = false;
bool shift_pressed = false;

void input_buffer_backspace() {
    if (input_buffer_occupancy > 0) {
        input_buffer_occupancy -= 1;
        input_buffer[input_buffer_occupancy] = 0;
    }
}

void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    if (!(scancode & 0x80)) { // Key press event               
        char character;

        // Handle Caps Lock press
        if (scancode == 0x3A) {
            caps_lock_active = !caps_lock_active;
            return;
        }

        // Handle Shift press
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = true;
        }

        // Handle backspace
        if (scancode == 0x0E) {
            input_buffer_backspace();
            handle_backspace();
            return;
        }

        character = ascii_lookup_table[scancode];

        // Adjustment for Caps Lock 
        if (caps_lock_active && character >= 'a' && character <= 'z') {
            character -= 32; 
        }

        // Adjustment for Shift
        if (shift_pressed) {
            if (character >= 'a' && character <= 'z' && !caps_lock_active) {
                character -= 32; // Lowercase to uppercase
            } else if (character >= '1' && character <= '9') {
                // Replace with logic to switch to symbols: '!', '@', '#' etc.
            } 
        }

        monitor_put(character);

    } else { // Key release event
         if (scancode == 0xAA || scancode == 0xB6) { // Shift key release
            shift_pressed = false;
        }
    }
}

void init_keyboard() {
    asm volatile ("sti");
    register_interrupt_handler(IRQ1, keyboard_handler);
}
