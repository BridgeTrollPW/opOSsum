#include "ps2keyboard.hpp"
#include "memory.hpp"

KeyCodes::KeyCodes()
{
    keyboardCodes[0x01].character = 'esc';
    keyboardCodes[0x02].character = '1';
    keyboardCodes[0x03].character = '2';
    keyboardCodes[0x04].character = '3';
    keyboardCodes[0x05].character = '4';
    keyboardCodes[0x06].character = '5';
    keyboardCodes[0x07].character = '6';
    keyboardCodes[0x08].character = '7';
    keyboardCodes[0x09].character = '8';
    keyboardCodes[0x0A].character = '9';
    keyboardCodes[0x0B].character = '0';

    keyboardCodes[0x0C].character = '-';
    keyboardCodes[0x0D].character = '=';
    keyboardCodes[0x0E].character = '\r';
    keyboardCodes[0x0F].character = '\t';

    keyboardCodes[0x10].character = 'q';
    keyboardCodes[0x11].character = 'w';
    keyboardCodes[0x12].character = 'e';
    keyboardCodes[0x13].character = 'r';
    keyboardCodes[0x14].character = 't';
    keyboardCodes[0x15].character = 'y';
    keyboardCodes[0x16].character = 'u';
    keyboardCodes[0x17].character = 'i';
    keyboardCodes[0x18].character = 'o';
    keyboardCodes[0x19].character = 'p';
    keyboardCodes[0x1A].character = '[';
    keyboardCodes[0x1B].character = ']';
    keyboardCodes[0x1C].character = '\n';
    keyboardCodes[0x1D].character = 'ctr-left';
    keyboardCodes[0x1E].character = 'a';
    keyboardCodes[0x1F].character = 's';
    keyboardCodes[0x20].character = 'd';
    keyboardCodes[0x21].character = 'f';
    keyboardCodes[0x22].character = 'g';
    keyboardCodes[0x23].character = 'h';
    keyboardCodes[0x24].character = 'j';
    keyboardCodes[0x25].character = 'k';
    keyboardCodes[0x26].character = 'l';
    keyboardCodes[0x27].character = ';';
    keyboardCodes[0x28].character = '\'';
    keyboardCodes[0x29].character = '`';
    keyboardCodes[0x2A].character = 'shift-left';
    keyboardCodes[0x2B].character = '\\';
    keyboardCodes[0x2C].character = 'z';
    keyboardCodes[0x2D].character = 'x';
    keyboardCodes[0x2E].character = 'c';
    keyboardCodes[0x2F].character = 'v';
    keyboardCodes[0x30].character = 'b';
    keyboardCodes[0x31].character = 'n';
    keyboardCodes[0x32].character = 'm';
    keyboardCodes[0x33].character = ',';
    keyboardCodes[0x34].character = '.';
    keyboardCodes[0x35].character = '/';
    keyboardCodes[0x36].character = 'shift-right';
    keyboardCodes[0x37].character = '*';
    keyboardCodes[0x38].character = 'left-alt';
    keyboardCodes[0x39].character = ' ';
    keyboardCodes[0x3A].character = 'capslock';
    keyboardCodes[0x3B].character = 'F1';
    keyboardCodes[0x3C].character = 'F2';
    keyboardCodes[0x3D].character = 'F3';
    keyboardCodes[0x3E].character = 'F4';
    keyboardCodes[0x3F].character = 'F5';

    
}

char KeyCodes::get(uint8_t scancode)
{
    return keyboardCodes[scancode].character;
}