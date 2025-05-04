#include "graphics_loader.hpp"

// Function to load graphics (currently just clears the screen)
void load_graphics() {
    // Placeholder for future graphics code
    // For now, just clear the screen to black
    unsigned char* vga_buffer = (unsigned char*)0xB8000;
    for (int i = 0; i < 80 * 25; ++i) {
        vga_buffer[i * 2] = ' ';     // Clear the character
        vga_buffer[i * 2 + 1] = 0x00; // Black background (no text)
    }

    // You can later expand this function to load custom graphics or images (PNG, BMP, etc.)
}
