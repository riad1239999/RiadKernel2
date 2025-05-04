#include "kernel.hpp"
#include "graphics_loader.hpp"  // Include the graphics loader (we'll create this later)

extern "C" void kernel_main() {
    // Set up a basic VGA text mode display
    init_vga();

    // Print a simple message to the screen
    print("Welcome to RiadsKernel2!\n");

    // Call the graphics loader (this function will later handle actual graphics)
    load_graphics();  // Placeholder function for graphics setup

    // Main infinite loop to prevent the kernel from exiting
    while (1) {
        // You can add more functionality here, like handling keyboard input or other tasks
    }
}

// Initialize VGA text mode display (80x25 character screen)
void init_vga() {
    unsigned char* vga_buffer = (unsigned char*)0xB8000;  // VGA text buffer address
    unsigned short color = 0x0F;  // White text on black background
    for (int i = 0; i < 80 * 25; ++i) {
        vga_buffer[i * 2] = ' ';      // Clear the character
        vga_buffer[i * 2 + 1] = color;  // Set the color of the text (white)
    }
}

// Print a string to the VGA screen
void print(const char* str) {
    unsigned char* vga_buffer = (unsigned char*)0xB8000;
    int i = 0;
    while (str[i] != '\0') {
        // Write the character and set the color
        vga_buffer[i * 2] = str[i];         // Character byte
        vga_buffer[i * 2 + 1] = 0x0F;      // White text color

        i++;
    }
}
