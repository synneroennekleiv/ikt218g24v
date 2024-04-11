extern _gdtp             ; _gdtp is a pointer in another file

global gdt_flush         ; Declare gdt_flush as a global symbol

gdt_flush:
    lgdt [_gdtp]        ; Load the GDT
    
    mov ax, 0x10        ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush     ; Jump to the 32-bit code segment (0x08) to start executing
.flush:
    ret                 ; Return from the gdt_flush function
