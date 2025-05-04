[bits 16]
[org 0x7C00]

; Set up the segment registers
mov ax, 0x07C0        ; Load the address where the bootloader will reside in memory
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax

; Switch to Protected Mode (32-bit)
cli                     ; Disable interrupts
lgdt [gdt_descriptor]    ; Load Global Descriptor Table
mov eax, cr0
or eax, 0x1              ; Set the protected mode bit in CR0
mov cr0, eax
jmp 0x08:protected_mode_entry  ; Jump to protected mode entry point

; GDT setup
gdt_start:
    ; Null descriptor
    dw 0x0000, 0x0000
    ; Code segment descriptor (32-bit)
    dw 0xFFFF, 0x0000, 0x9A, 0xCF
    ; Data segment descriptor (32-bit)
    dw 0xFFFF, 0x0000, 0x92, 0xCF
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

protected_mode_entry:
    ; Switch to 32-bit mode
    mov ax, 0x10         ; Code segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Load the kernel (assuming it's located at 0x10000 in memory)
    mov ebx, 0x10000     ; Kernel start address
    mov esi, 0x2000      ; Size of kernel
    mov edi, 0x10000     ; Kernel load address
    call load_kernel

    ; Jump to kernel entry point
    jmp 0x08:kernel_entry

load_kernel:
    ; Copy kernel to memory (very basic)
    mov ecx, esi
    rep movsb
    ret

kernel_entry:
    ; This is where control is transferred to the kernel
    jmp 0x08:kernel_main
