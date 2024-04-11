#include <gdt.h>

#define ENTRIES 5

// Store GDT entries and pointer
struct gdt_entry_struct gdt_entries[ENTRIES];
struct gdt_ptr_struct _gdtp;

void gdt_load(struct gdt_ptr_struct *_gdtp) {
    asm volatile("lgdt %0" : : "m" (*_gdtp));
}

// Function to initialize the GDT
void init_gdt() {
    // Setting the limit of the GDT and then set the base address
    _gdtp.limit = sizeof(struct gdt_entry_struct) * ENTRIES - 1;
    _gdtp.base = (uint32_t)&gdt_entries;

    // Set up individual GDT entries
    set_gdt_gate(0,0,0,0,0);                  // null segment
    set_gdt_gate(1,0,0xFFFFFFFF, 0x9A, 0xCF); // kernel code segment
    set_gdt_gate(2,0,0xFFFFFFFF, 0x92, 0xCF); // kernel data segment
    set_gdt_gate(3,0,0xFFFFFFFF, 0xFA, 0xCF); // user code segment
    set_gdt_gate(4,0,0xFFFFFFFF, 0xF2, 0xCF); // user data segment

    // Load the GDT
    gdt_load(&_gdtp);
    
    gdt_flush((uint32_t)&_gdtp);
}

// Function to set up a GDT entry
void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {

    // Base address
    gdt_entries[num].base_low = (base & 0xFFFF); // lower 16 bits
    gdt_entries[num].base_middle = (base >> 16) & 0xFF; // middle 8 bits
    gdt_entries[num].base_high = (base >> 24) & 0xFF; // upper 8 bits

    // Limit
    gdt_entries[num].limit_low = (limit & 0xFFFF); // lower 16 bits

    // Flags and upper 4 bits of limit
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    // Access byte
    gdt_entries[num].access = access;
}   
