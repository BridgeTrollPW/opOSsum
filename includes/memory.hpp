#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "types.hpp"

void *memset(void *s, int c, size_t len)
{
    unsigned char *dst = (unsigned char *)s;
    while (len > 0)
    {
        *dst = (unsigned char)c;
        dst++;
        len--;
    }
    return s;
}

#endif