#include "vga.hpp"
#include "io.hpp"

Screen::Screen()
{
    vga = (uint16_t *)0xB8000;
    setColor(COLOR::WHITE, COLOR::BLACK);
    setPosition(0, 0);
}

void Screen::setColor(COLOR fg, COLOR bg)
{
    cellAttribute = fg | bg << 4;
}

uint8_t Screen::getColor()
{
    return cellAttribute;
}

void Screen::setPosition(int x, int y)
{
    position = calcCursorPosition(x, y);
    outb(portCommand, commandHighByte);
    outb(portData, ((position >> 8) & 0x00FF));
    outb(portCommand, commandLowByte);
    outb(portData, position & 0x00FF);
}

int Screen::calcCursorPosition(int x, int y)
{
    if (x > maxWidth)
    {
        x = 0;
        ++y;
    }
    if (y > maxHeight)
    {
        y = 0;
    }
    return (y * maxWidth) + x;
}

int Screen::getPositionX()
{
    return position % maxWidth;
}
int Screen::getPositionY()
{
    return (position - getPositionX()) / 80;
}

int Screen::putchar(int ic)
{
    vga[position] = ((char)ic) | (cellAttribute << 8);
    setPosition(getPositionX() + 1, getPositionY());
    return ic;
}