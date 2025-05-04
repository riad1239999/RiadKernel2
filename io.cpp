#include "io.hpp"
#include <stdint.h>

// Function to send a byte to a port
inline void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
}
