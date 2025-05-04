[bits 32]
[global kernel_main]

; Entry point for kernel in protected mode
kernel_main:
    ; Set up a simple stack
    mov esp, 0x90000      ; Stack pointer

    ; Jump to kernel entry in C++ (the kernel_main function in kernel.cpp)
    call kernel_main_cpp

    ; Hang the system (infinite loop)
    jmp $
