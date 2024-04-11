#include <screen.h>
#include <libc/string.h>
#include <libc/stdmemory.h>

#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

uint16_t *text_ptr;
int attribute = 0x0F;
int cursor_x = 0, cursor_y = 0;

// Call to initialize screen before using it
void init_screen(void) {
    text_ptr = (uint16_t *)VGA_ADDRESS;
    clear();
}

// Function to scroll the cursor and text, so that when the cursor goes down the screen
// this function will act and copy visible text to a buffer and move it up to the top
void scroll(void) {
    unsigned space, temp;

    space = 0x20 | (attribute << 8);
    if(cursor_y >= VGA_ROWS) {
        temp = cursor_y - VGA_ROWS + 1; // Scroll up
        memcopy(text_ptr, text_ptr + temp * VGA_COLS, (VGA_ROWS - temp) * VGA_COLS * 2); // Copy the content in memory buffer
        memset(text_ptr + (VGA_ROWS - temp) * VGA_COLS, space, VGA_COLS); // Writing spaces to the roll

        cursor_y = VGA_ROWS - 1; // Set cursor to the last line
    }
}

// Function to display the cursor blinker position to the terminal
void cursor_blinker(void) {
    unsigned temp;

    temp = cursor_y *VGA_COLS + cursor_x;

    // VGA Controller
    outb(0x3D4, 14);            // Select high register
    outb(0x3D5, temp >> 8);     // Write position of cursor to high register
    outb(0x3D4, 15);            // Select low register
    outb(0x3D5, temp);          // Write position of cursor to low register
}

void set_text_color(uint8_t background_color, uint8_t foreground_color) {
    attribute = (background_color << 4) | (foreground_color & 0x0F);
}

void clear(void) {
    unsigned space;

    space = 0x20 | (attribute << 8);

    for(int i = 0; i < 25; i++) {
        memset(text_ptr + i * VGA_COLS, space, VGA_COLS);
    }

    cursor_x = 0;
    cursor_y = 0;

    cursor_blinker();
}

void putchar(uint8_t c) {
    uint16_t *where;
    unsigned attr_color = attribute << 8;

    if (c == 0x08 && cursor_x != 0) { cursor_x--; }             // Backspace (0x08), move cursor back one space
    if (c == 0x09) { cursor_x = (cursor_x + 8) & ~(8 - 1); }    // Tab (0x09), but only if divisible by 8
    if (c == '\r') { cursor_x = 0; }                            // Home key, return to leftmost margin  
    if (c == '\n') { cursor_x = 0; cursor_y++; }                // Enter key, return to leftmost margin

    // Printable characters from 'space' (1st printable char) and onward.
    if (c >= ' ') {
        where = text_ptr + (cursor_y * 80 + cursor_x);
        *where = c | attr_color;
        cursor_x++;
    }

    if (cursor_x >= VGA_COLS) { cursor_x = 0; cursor_y++; } // Newline when we hit the last column (rightmost).

    scroll();
    cursor_blinker();
}

void putstring(uint8_t *string) {
    for (int i = 0; i < string_length(string); i++) {
        putchar(string[i]); // Loop provided buffer and print characters.
    }
}