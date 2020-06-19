#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdarg.h>

#include <string.hpp>

#define EOF (-1)

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
    WHITE = 15
};

class Screen
{
private:
    uint16_t *vga;
    int maxWidth = 80;
    int maxHeight = 25;
    uint8_t cellAttribute;
    uint16_t position;

    const int portCommand = 0x3D4;
    const int portData = 0x3D5;
    const int commandHighByte = 14;
    const int commandLowByte = 15;

public:
    Screen();
    void setColor(COLOR fg, COLOR bg);
    void setPosition(int x, int y);
    int getPositionX();
    int getPositionY();
    uint8_t getColor();
    int calcCursorPosition(int x, int y);
    int putchar(int ic);
    void clear();

    bool print(const char *data, size_t length)
    {
        const unsigned char *bytes = (const unsigned char *)data;
        for (size_t i = 0; i < length; i++)
            if (putchar(bytes[i]) == EOF)
            {
                return false;
            }
        return true;
    }

    int printf(const char *format, ...)
    {
        va_list parameters;
        va_start(parameters, format);

        int written = 0;

        while (*format != '\0')
        {
            size_t maxrem = INT_MAX - written;

            if (format[0] != '%' || format[1] == '%')
            {
                if (format[0] == '%')
                    format++;
                size_t amount = 1;
                while (format[amount] && format[amount] != '%')
                    amount++;
                if (maxrem < amount)
                {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(format, amount))
                    return -1;
                format += amount;
                written += amount;
                continue;
            }

            const char *format_begun_at = format++;

            if (*format == 'c')
            {
                format++;
                char c = (char)va_arg(parameters, int /* char promotes to int */);
                if (!maxrem)
                {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(&c, sizeof(c)))
                    return -1;
                written++;
            }
            else if (*format == 's')
            {
                format++;
                const char *str = va_arg(parameters, const char *);
                size_t len = strlen(str);
                if (maxrem < len)
                {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(str, len))
                    return -1;
                written += len;
            }
            else
            {
                format = format_begun_at;
                size_t len = strlen(format);
                if (maxrem < len)
                {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(format, len))
                    return -1;
                written += len;
                format += len;
            }
        }

        va_end(parameters);
        return written;
    }
};

#endif