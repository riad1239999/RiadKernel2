#include "vga.hpp"
#include <stdint.h>

// VGA memory start address (for graphic mode)
#define VGA_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// Pointer to the VGA memory
uint8_t* vga = (uint8_t*)VGA_MEMORY;

// Function to initialize the VGA (set to graphic mode)
void init_vga() {
    // Set the VGA mode to 0x13 (320x200, 256 colors)
    __asm__ __volatile__("movb $0x13, %al\n\t"
                         "int $0x10");  // BIOS interrupt to set video mode
}

// Function to draw a pixel on the screen at (x, y) with a specific color
void draw_pixel(int x, int y, uint8_t color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; // Out of bounds check
    }
    // Write color data to the VGA memory at the specified position
    vga[y * SCREEN_WIDTH + x] = color;
}

// Function to clear the screen (set all pixels to black)
void clear_screen() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            draw_pixel(x, y, 0); // 0 is black
        }
    }
}
