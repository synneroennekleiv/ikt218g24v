#ifndef IDT_H
#define IDT_H

#include <libc/stdint.h>

#define IDT_ENTRIES 256

void idt_load(struct idt_ptr_struct *_idtp);

void register_int_handler(int num, void (*handler)(void *data), void *data);

void default_int_handler(void *data);

void int_handler(int num);

struct int_handler {
    uint16_t num;
    void (*handler)(void *data);
    void *data;
}__attribute__((packed));

struct idt_entry_struct {
    uint16_t base_low;
    uint16_t base_high;
    uint16_t sel; // Kernel segment
    uint8_t null; 
    uint8_t flags;
}__attribute__((packed));

struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
 }__attribute__((packed));

void idt_set_gate(int32_t num, uint32_t base, uint16_t sel, uint8_t flags);

void idt_init();

#endif // IDT_H
