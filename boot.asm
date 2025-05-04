[org 0x7C00]
bits 16

start:
    ; Print "Booting RiadsKernel2..."
    mov si, message
.print:
    lodsb                   ; Load next byte from [SI] into AL
    or al, al               ; Check if it's null terminator
    jz .done
    mov ah, 0x0E            ; BIOS teletype function
    int 0x10                ; Print AL
    jmp .print

.done:
    ; Read 5 sectors starting from LBA sector 2 into 0x1000:0000
    mov ah, 0x02            ; BIOS read sector function
    mov al, 5               ; Number of sectors to read
    mov ch, 0               ; Cylinder
    mov cl, 2               ; Sector 2 (first sector after bootloader)
    mov dh, 0               ; Head
    mov dl, 0               ; Drive (floppy/hard disk)
    mov bx, 0x0000
    mov es, 0x1000          ; ES:BX = 0x1000:0000 (linear = 0x10000)
    int 0x13                ; Call BIOS to read disk
    jc fail                 ; If failed, jump to error

    jmp 0x1000:0000         ; Jump to loaded kernel

fail:
    mov si, failmsg
.failprint:
    lodsb
    or al, al
    jz $
    mov ah, 0x0E
    int 0x10
    jmp .failprint

message db "Booting RiadsKernel2...", 0
failmsg db "Disk load failed!", 0

; Pad the rest of the boot sector to 510 bytes
times 510-($-$$) db 0
dw 0xAA55   ; Boot sector signature
