//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#include "io_ports.h"
#include "isr.h"
#include "monitor.h"
#include <libc/string.h>
#include "keyboard.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    if(regs.int_no == 33){
        keyboard_handler();
    }
   monitor_write("recieved interrupt: ");
   monitor_write_dec(regs.int_no);
   monitor_put('\n');
}

static void itoa(uint32_t value, char *str, int base) {
    char *ptr;
    char *low;

    // Check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return;
    }

    ptr = str;

    // Remember where the numbers start.
    low = ptr;

    // The actual conversion.
    do {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + value % base];
        value /= base;
    } while (value);

    // Terminator.
    *ptr-- = '\0';

    // Reverse the string.
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    // The function now correctly does not return any value.
}


// Function to write a decimal number on the screen.
void monitor_write_dec(uint32_t n) {
    char buf[16];
    itoa(n, buf, 10);  // Convert n to a decimal string
    monitor_write(buf);
}

// Function to write a hexadecimal number on the screen.
void monitor_write_hex(uint32_t n) {
    char buf[16];
    itoa(n, buf, 16);  // Convert n to a hexadecimal string
    monitor_write(buf);
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}
// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}