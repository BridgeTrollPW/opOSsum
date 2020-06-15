#ifndef VGA_HPP
#define VGA_HPP

#include <stdint.h>

enum COLOR
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};

class VGA
{

    // This is the x86's VGA textmode buffer. To display text, we write data to this memory location
    volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;
    // By default, the VGA textmode buffer has a size of 80x25 characters
    const int VGA_COLS = 80;
    const int VGA_ROWS = 25;

    // We start displaying text in the top-left of the screen (column = 0, row = 0)
    int column = 0;
    int row = 0;
    uint8_t term_color = 0x0F; // Black background, White foreground

public:
    VGA();

    void putc(char c);
    void print(const char *str);
    void setColor(uint8_t color);
    void setColor(COLOR fg, COLOR bg);
    void reset();
    void update();
    void redraw();
};

#endif