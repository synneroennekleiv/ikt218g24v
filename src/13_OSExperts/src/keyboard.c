#include "libc/stdint.h"
#include "descriptor_tables.h"
#include "util.h"
#include "libc/stdio.h"
#include "keyboard.h"
#include "libc/stdbool.h"
#include <io_ports.h>
#include <isr.h>
#include <monitor.h>

static unsigned char ascii_lookup_table[128] =
        {
                0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
                'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
                'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
                'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };



uint8_t input_buffer_occupancy = 0;
char input_buffer[256];


void input_buffer_backspace() {
  if (input_buffer_occupancy > 0) {
    input_buffer_occupancy -= 1;
    input_buffer[input_buffer_occupancy] = 0;
  }
}

void keyboard_handler()
{
    uint8_t scancode = inb(0x60);
    /*monitor_put('\n');
    monitor_write_dec(scancode);
    monitor_put('\n');*/

    if(!(scancode & 0x80))
    {
        char character;

        // Handle backspace
        if (scancode == 0x0E) {
        input_buffer_backspace();
        handle_backspace();
        return;
        }

        character = ascii_lookup_table[scancode];
        monitor_put(character);

    
        //if(scancode < sizeof(ascii_lookup_table)){
        //    character = scancode;
        //}

        // Print the character if it's not a special key

        //if(character != 0){
        //    monitor_put(character);
        //}
    }



}

void init_keyboard(){
        asm volatile ("sti");
        register_interrupt_handler(IRQ1, keyboard_handler);
}