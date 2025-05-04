#ifndef KERNEL_HPP
#define KERNEL_HPP

// Declaration of functions used in kernel.cpp
void kernel_main();      // Entry point for the kernel
void init_vga();         // Initializes VGA text mode for display
void print(const char*); // Prints a string to the VGA screen

#endif
