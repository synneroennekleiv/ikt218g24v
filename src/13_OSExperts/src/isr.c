// Inspired from the James Molloy's implementation tutorial for GDT and IDT: https://archive.is/L3pyA

#include <libc/stdio.h>
#include <libc/global.h>
#include <isr.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_handler(reg_t regs) {
    if(interrupt_handlers[regs.int_num] != 0) {
        isr_t handler = interrupt_handlers[regs.int_num];
        handler(regs);
    }
    else {
        // Prints the interrupt number and info to the screen
        printf("Received interrupt: %d - %s\n", regs.int_num, message_exception[regs.int_num]);
    }
}

void irq_handler(reg_t regs) {
    // Send an EOI to the slave controller
    if(regs.int_num >= 40) {
        outb(0xA0, 0x20);
    }

    outb(0x20, 0x20);

    // Calls the interrupt handler
    if(interrupt_handlers[regs.int_num] != 0) {
        isr_t handler = interrupt_handlers[regs.int_num];
        handler(regs);
    }
}