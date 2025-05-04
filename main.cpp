#include "vga.hpp"
#include "timer.hpp"

void kernel_main() {
    init_vga();  // Initialize the graphics driver
    init_timer(50);  // Initialize timer with 50Hz frequency (for time management)

    clear_screen();  // Clear the screen (set to black)

    // Add further OS initialization, kernel logic, and interrupt handling here
}
