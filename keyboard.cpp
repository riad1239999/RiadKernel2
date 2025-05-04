#include "keyboard.hpp"
#include "io.hpp"
#include <stdint.h>

#define KEYBOARD_PORT 0x60  // The keyboard data port
#define KEYBOARD_CMD_PORT 0x64  // The keyboard command port

// Function to initialize the keyboard (set up the IRQ handler)
void init_keyboard() {
    // Set up the interrupt handler for IRQ1 (keyboard)
    // Assuming you're using IDT (interrupt descriptor table)
    // This should connect IRQ1 to the keyboard_handler

    // Send a command to the keyboard (e.g., enable the keyboard)
    outb(KEYBOARD_CMD_PORT, 0xAE);  // Enable keyboard interrupt
}

// Function to handle keyboard interrupts (scancode reading)
void keyboard_handler() {
    // Read the scancode from the keyboard data port
    uint8_t scancode = inb(KEYBOARD_PORT);

    // Process the scancode (e.g., convert it to a character, etc.)
    // For simplicity, we'll print out the scancode for now
    // Here you can add your own logic to map the scancode to an ASCII character
    // For example:
    // if (scancode == 0x1E) { // 'A' key
    //     print_char('A');
    // }
}
