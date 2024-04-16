// io_ports.h -- Defines functions for interacting with hardware I/O ports.

#ifndef IO_PORTS_H
#define IO_PORTS_H

#include "libc/stdint.h" // Or directly include your typedefs here if not using common.h

// Function to write a byte to an I/O port
void outb(uint16_t port, uint8_t value);

// Function to read a byte from an I/O port
uint8_t inb(uint16_t port);

// Function to read a word from an I/O port
uint16_t inw(uint16_t port);

#endif // IO_PORTS_H
