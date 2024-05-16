#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <monitor.h>
#include <keyboard.h>
#include <descriptor_tables.h>
#include <keyboard.h>
#include <isr.h>
#include <memory/memory.h>
#include <libc/stdio.h>


// Declare the GDT initialization function implemented in assembly
extern void init_gdt();

// Structure representing the Multiboot information
struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

// Declare the kernel_main function
int kernel_main();

extern uint32_t end;

// Entry point when the bootloader starts executing the kernel
int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    // Initialize the Global Descriptor Table (GDT)
    init_gdt();
    init_idt();
    init_keyboard();

    
    
    // Print "Hello World" to the console using printf-like function
    monitor_write("Hello world");
    init_kernel_memory(&end);
    print_memory_layout();
    paging_init();
    //asm volatile ("int $0x8");
    //asm volatile ("int $0x4");


    printf("test print PLS");
    

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}