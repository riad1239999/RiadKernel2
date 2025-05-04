#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <stdint.h>

// Declare the main entry point for the kernel
extern "C" void kernel_main();  // This is the entry point, declared as "C" to prevent name mangling

// Define IRQ numbers (just as an example)
#define IRQ0 32  // Timer interrupt
#define IRQ1 33  // Keyboard interrupt
#define IRQ12 44 // Mouse interrupt

// Forward declare keyboard and mouse handlers (or other interrupts)
void keyboard_handler();
void mouse_handler();

// Basic interrupt handler setup (you can expand this further in the implementation)
void init_idt();  // Initializes the Interrupt Descriptor Table (IDT)

// Forward declare any other functions that are part of the kernel
void handle_keyboard_input(uint8_t scancode); // Example function to handle keyboard input
bool keyboard_input_ready(); // Example function to check if input is ready

#endif // KERNEL_HPP
