#include "vga.hpp"
#include "timer.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

void kernel_main() {
    init_keyboard();  // Initialize the keyboard driver
    init_mouse();     // Initialize the mouse driver

    // More initialization code can follow...
}
