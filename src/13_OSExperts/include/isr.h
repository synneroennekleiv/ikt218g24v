// Inspired from the James Molloy's implementation tutorial for GDT and IDT: https://archive.is/L3pyA

#ifndef ISR_H
#define ISR_H

#include <libc/stdint.h>

#define IRQ_COUNT 16

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct reg
{
    uint32_t ds;
    uint32_t edi, esi, edp, ebx, edx, ecx, eax;
    uint32_t int_num, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
} reg_t;

typedef void (*isr_t)(reg_t);
void register_interrupt_handler(uint8_t n, isr_t handler);

void (*irq_handlers[IRQ_COUNT])(void);

void init_irq();

void register_irq_handler(int irq, void (*handler)(void));

static const char *message_exception[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check"
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Reserved" 
};

#endif // ISR_H