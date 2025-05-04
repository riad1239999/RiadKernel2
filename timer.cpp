#include "timer.hpp"
#include <stdint.h>
#include <io.h>

#define PIT_COMMAND_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40

// Function to initialize the timer (PIT - Programmable Interval Timer)
void init_timer(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency; // PIT operates at 1.193180 MHz

    // Send command to PIT to set the frequency
    outb(0x36, PIT_COMMAND_PORT); // Command for channel 0, mode 3 (square wave)
    outb(divisor & 0xFF, PIT_CHANNEL0_PORT); // Send low byte of divisor
    outb((divisor >> 8) & 0xFF, PIT_CHANNEL0_PORT); // Send high byte of divisor
}

// Timer interrupt handler
void timer_handler() {
    // This will be called periodically based on the set frequency
    // Update system time, manage scheduling, etc.
}
