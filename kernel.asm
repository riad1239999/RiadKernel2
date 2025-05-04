[BITS 16]            ; We are in 16-bit mode when the bootloader starts
[ORG 0x10000]        ; Kernel is loaded to address 0x10000 (64KB from the start)

start:
    cli                 ; Disable interrupts
    lgdt [gdt_descriptor]   ; Load the GDT (Global Descriptor Table)

    ; Set the PE bit (Protection Enable) in CR0 to switch to protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump to flush the pipeline and enter protected mode
    jmp CODE_SEG:init_pm

; -------------------
; GDT (Global Descriptor Table) for Protected Mode
; -------------------
gdt_start:
gdt_null:  dq 0                 ; Null descriptor (required)
gdt_code:  dw 0xFFFF            ; Code segment limit
           dw 0x0000            ; Code segment base (low)
           db 0x00              ; Code segment base (middle)
           db 10011010b         ; Access byte (present, ring 0, code segment)
           db 11001111b         ; Granularity (4KB, 32-bit)
           db 0x00              ; Code segment base (high)

gdt_data:  dw 0xFFFF            ; Data segment limit
           dw 0x0000            ; Data segment base (low)
           db 0x00              ; Data segment base (middle)
           db 10010010b         ; Access byte (present, ring 0, data segment)
           db 11001111b         ; Granularity
           db 0x00              ; Data segment base (high)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1    ; Size of the GDT - 1
    dd gdt_start                  ; Pointer to the start of the GDT

CODE_SEG equ 0x08                ; Code segment selector (GDT entry 1)
DATA_SEG equ 0x10                ; Data segment selector (GDT entry 2)

; -------------------
; Protected Mode Entry Point (32-bit mode)
; -------------------
[BITS 32]                        ; Now we are in 32-bit mode
init_pm:
    mov ax, DATA_SEG             ; Load data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000             ; Set up the stack

    call kernel_main             ; Call the main C++ kernel function

hang:
    cli
    hlt                          ; Halt the CPU
    jmp hang                     ; Infinite loop to prevent further execution
