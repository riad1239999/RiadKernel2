#ifndef IO_HPP
#define IO_HPP

#include <stdint.h>

// Function to send a byte to a port
inline void outb(uint16_t port, uint8_t value);

// Function to read a byte from a port
inline uint8_t inb(uint16_t port);

#endif // IO_HPP
