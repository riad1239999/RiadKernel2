ENTRY(kernel_main)

SECTIONS {
    . = 0x10000; /* The kernel is loaded at address 0x10000 */

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
