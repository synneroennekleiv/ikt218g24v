#include <idt.h>
#include <libc/stdmemory.h>
#include <libc/stddef.h>

struct idt_entry_struct idt_entries[IDT_ENTRIES];
struct int_handler interrupt_handlers[IDT_ENTRIES];
struct idt_ptr_struct _idtp;

void idt_set_gate(int32_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;                            
    idt_entries[num].null = 0;
    idt_entries[num].flags = flags;
}

void idt_init() {
    _idtp.limit = sizeof (struct idt_entry_struct) * IDT_ENTRIES - 1;
    _idtp.base = (uint32_t)&idt_entries;

    //memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    for(int i = 0; i < IDT_ENTRIES; i++) {
        idt_entries[i].base_low = 0x0000;
        idt_entries[i].base_high = 0x0000;
        idt_entries[i].sel = 0x08;
        idt_entries[i].null = 0x00;
        idt_entries[i].flags = 0x8E;

        interrupt_handlers[i].handler = NULL;
    }

    idt_load(&_idtp);
} 

void register_int_handler(int num, void (*handler)(void *data), void *data) {
    interrupt_handlers[num].num = num;
    interrupt_handlers[num].handler = handler;
    interrupt_handlers[num].data = data;
}

void int_handler(int num) {
    if(interrupt_handlers[num].handler != NULL) {
        interrupt_handlers[num].handler(interrupt_handlers[num].data);
    }
    else {
        default_int_handler(NULL);
    }
}

void idt_load(struct idt_ptr_struct *_idtp) {
    asm volatile("lidt %0" : : "m" (*_idtp));
}