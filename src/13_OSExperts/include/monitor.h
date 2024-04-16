// monitor.h -- Defines the interface for the monitor

#ifndef MONITOR_H
#define MONITOR_H

#include "io_ports.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void monitor_write_dec(uint32_t n);
void monitor_write_hex(uint32_t n);

#endif // MONITOR_H
