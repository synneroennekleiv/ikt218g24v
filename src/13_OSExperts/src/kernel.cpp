
extern "C"{
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
    #include <system.h>
    #include <libc/stdio.h>
}



// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}




extern "C" int kernel_main(void);

int kernel_main() {
    

   // Trigger interrupts to test handlers
    /*asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    // Enable interrupts
    asm volatile("sti");*/




    //void* some_memory = malloc(12345); 
    //void* memory2 = malloc(54321); 
    //void* memory3 = malloc(13331);
    //char* memory4 = new char[1000]();



    // Main loop
    /*printf("Kernel main loop\n");
    while(true) {
        // Kernel main tasks
    }

    // This part will not be reached
    printf("Done!\n");*/

    while(1);


    return 0;
}