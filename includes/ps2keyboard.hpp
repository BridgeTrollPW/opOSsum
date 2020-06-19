#ifndef PS2_KEYBOARD_HPP
#define PS2_KEYBOARD_HPP

#include <stdint.h>

struct scancode{
    uint8_t code;
    char character;
};

class KeyCodes{
    scancode keyboardCodes[215];
public:
    KeyCodes();
    char get(uint8_t scancode);
};


#endif