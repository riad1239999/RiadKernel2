#include "kernel.hpp"
#include "interrupts.hpp"   // For IDT initialization
#include "io.hpp"           // For I/O operations (inb and outb)
#include "keyboard.hpp"     // For keyboard handling
#include "mouse.hpp"        // For mouse handling

// Main entry point of the kernel
void kernel_main() {
    // Initialize interrupt descriptor table (IDT) and enable interrupts
    init_idt();
    
    // Basic kernel initialization
    // You can initialize other components here such as memory management, drivers, etc.
    
    // Example of using inb() and outb()
    uint8_t status = inb(0x64);  // Read keyboard controller status (just as an example)
    outb(0x60, 0xFF);            // Write to port 0x60 (just as an example)

    // Main kernel loop (this is just a placeholder)
    // The kernel will run in this loop, handling interrupts, and performing tasks.
    while (true) {
        // Your kernel logic here (e.g., handle system calls, tasks, etc.)
        
        // Example: Checking for keyboard input (simplified)
        // This could be triggered by the IRQ handler in your interrupt setup
        if (keyboard_input_ready()) {
            uint8_t scancode = inb(0x60);  // Get keyboard scancode
            handle_keyboard_input(scancode);
        }

        // Other kernel tasks...
    }
}

// This function would be used to check if keyboard input is ready (as an example)
bool keyboard_input_ready() {
    // Check the status register of the keyboard (just an example)
    uint8_t status = inb(0x64);
    return (status & 0x01) != 0;  // If the data bit is set, input is ready
}

// Example of handling keyboard input (very simple)
void handle_keyboard_input(uint8_t scancode) {
    // Here you can map the scancode to a key and handle the input
    // For example, printing the key to the screen (just a placeholder)
    if (scancode == 0x1E) {
        // 'A' key (just an example)
        // You can implement more complex behavior here, like printing to screen
        // or adding to a buffer for further processing.
    }
}

