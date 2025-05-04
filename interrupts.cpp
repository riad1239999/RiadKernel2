#include "interrupts.hpp"
#include "keyboard.hpp"  // For keyboard_handler
#include "mouse.hpp"     // For mouse_handler

// Include necessary architecture-dependent files (e.g., for setting up the IDT)
#include "io.hpp"
#include <stdint.h>

// Placeholder function for setting interrupt handlers
void set_interrupt_handler(uint8_t irq, void (*handler)()) {
    // In a real kernel, this function will configure the IDT entry
    // for the given IRQ and link it to the handler function.
    // This is a simplified example.
}

// Initialize the Interrupt Descriptor Table (IDT)
void init_idt() {
    // Set up IRQ1 for keyboard
    set_interrupt_handler(IRQ1, keyboard_handler);

    // Set up IRQ12 for mouse
    set_interrupt_handler(IRQ12, mouse_handler);

    // Enable interrupts
    __asm__ __volatile__("sti");
}
