#include <stddef.h>
#include "vga.hpp"

VGA::VGA()
{
    // Clear the textmode buffer
    for (int col = 0; col < VGA_COLS; col++)
    {
        for (int row = 0; row < VGA_ROWS; row++)
        {
            // The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
            // Given this, we find an index into the buffer for our character
            const size_t index = (VGA_COLS * row) + col;
            // Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
            // - B is the background color
            // - F is the foreground color
            // - C is the ASCII character
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' '; // Set the character to blank (a space character)
        }
    }
}

void VGA::reset()
{
    column = 0;
    row = 0;
    // Clear the textmode buffer
    for (int col = 0; col < VGA_COLS; col++)
    {
        for (int row = 0; row < VGA_ROWS; row++)
        {
            // The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
            // Given this, we find an index into the buffer for our character
            const size_t index = (VGA_COLS * row) + col;
            // Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
            // - B is the background color
            // - F is the foreground color
            // - C is the ASCII character
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' '; // Set the character to blank (a space character)
        }
    }
}

void VGA::redraw()
{
    for (int col = 0; col < VGA_COLS; col++)
    {
        for (int row = 0; row < VGA_ROWS; row++)
        {
            const size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = vga_buffer[index];
        }
    }
}

void VGA::update()
{
    for (int col = 0; col < VGA_COLS; col++)
    {
        for (int row = 0; row < VGA_ROWS; row++)
        {
            const size_t index = (VGA_COLS * row) + col;
            char c = vga_buffer[index];
            vga_buffer[index] = (((uint16_t)term_color << 8) | (c & 0xff));
        }
    }
}

void VGA::putc(char c)
{
    // Remember - we don't want to display ALL characters!
    switch (c)
    {
    case '\n': // Newline characters should return the column to 0, and increment the row
    {
        column = 0;
        row++;
        break;
    }

    case '\t': // Newline characters should return the column to 0, and increment the row
    {
        column = column + 4;
        break;
    }

    default: // Normal characters just get displayed and then increment the column
    {
        const size_t index = (VGA_COLS * row) + column; // Like before, calculate the buffer index
        vga_buffer[index] = ((uint16_t)term_color << 8) | c;
        column++;
        break;
    }
    }

    // What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
    if (column >= VGA_COLS)
    {
        column = 0;
        row++;
    }

    // What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
    if (row >= VGA_ROWS)
    {
        column = 0;
        row = 0;
    }
}

void VGA::print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        putc(str[i]);
    }
}

void VGA::setColor(COLOR fg, COLOR bg)
{
    setColor((fg | bg << 4));
}

void VGA::setColor(uint8_t color)
{
    term_color = color;
}