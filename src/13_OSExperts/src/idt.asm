extern _idtp      ; Pointer for another file

global idt_load

idt_load:
    lidt [_idtp]  ; Load pointer
    ret