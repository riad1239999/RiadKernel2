; kernel.asm
[global _start]      ; Entry point for the bootloader to jump to the kernel
[extern kernel_main] ; Declaring the kernel_main function, which is written in C++

; The bootloader will jump to _start in this file

_start:
    cli                      ; Clear interrupts
    mov esp, 0x9C00           ; Set up a basic stack at 0x9C00 (you can modify this as needed)
    
    ; Set up segment registers (just as an example, you may need to modify this for your OS)
    mov ax, 0x10              ; Set data segment to 0x10 (assume this is initialized in GDT)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Jump to kernel_main function in C++
    ; This is where the kernel code will start running
    call kernel_main          ; Call kernel_main, defined in kernel.cpp

    ; Halt the system in case kernel_main ends (this should never happen)
halt:
    hlt                       ; Halt the CPU (infinite loop, system will stop here)
    jmp halt                  ; Jump to halt if the system was somehow resumed
