#include "vga.hpp"
#include "utils.hpp"
#include "idt.hpp"
#include "io.hpp"

#define EXP_A 184
#define EXP_C 16249

float EXP(float y)
{
    union {
        float d;
        struct
        {
#ifdef LITTLE_ENDIAN
            short j, i;
#else
            short i, j;
#endif
        } n;
    } eco;
    eco.n.i = EXP_A * (y) + (EXP_C);
    eco.n.j = 0;
    return eco.d;
}

float LOG(float y)
{
    int *nTemp = (int *)&y;
    y = (*nTemp) >> 16;
    return (y - EXP_C) / EXP_A;
}

float POW(float b, float p)
{
    return EXP(LOG(b) * p);
}

int hex2dec(unsigned char *hex)
{
    int result = 0;
    int length = strlen(hex);
    for (int i = 0; i < length; i++)
    {
        if (hex[i] >= 48 && hex[i] <= 57)
        {
            result += (hex[i] - 48) * POW(16, length - i - 1);
        }
        else if (hex[i] >= 65 && hex[i] <= 70)
        {
            result += (hex[i] - 55) * POW(16, length - i - 1);
        }
        else if (hex[i] >= 97 && hex[i] <= 102)
        {
            result += (hex[i] - 87) * POW(16, length - i - 1);
        }
    }
    return result;
}

#define KBD_DATA_PORT 0x60

/** read_scan_code:
     *  Reads a scan code from the keyboard
     *
     *  @return The scan code (NOT an ASCII character!)
     */
unsigned char read_scan_code()
{
    return inb(KBD_DATA_PORT);
}

extern "C" void kernel_main()
{
    IDT idt;
    VGA vga;

    auto line = [&vga]() -> void {
        vga.setColor(COLOR::BLUE, COLOR::BLACK);
        for (size_t i = 0; i < 80; i++)
        {
            vga.putc(char(205));
        }
    };

    line();
    vga.setColor(COLOR::RED, COLOR::BLACK);
    vga.print(R"(         @@@@@@  @@@@@@@   @@@@@@   @@@@@@  @@@@@@ @@@  @@@ @@@@@@@@@@ 
        @@!  @@@ @@!  @@@ @@!  @@@ !@@     !@@     @@!  @@@ @@! @@! @@!
        @!@  !@! @!@@!@!  @!@  !@!  !@@!!   !@@!!  @!@  !@! @!! !!@ @!@
        !!:  !!! !!:      !!:  !!!     !:!     !:! !!:  !!! !!:     !!:
         : :. :   :        : :. :  ::.: :  ::.: :   :.:: :   :      :  
)");

    line();
    vga.setColor(COLOR::WHITE, COLOR::BLACK);
    unsigned char scancode;
    char *str;
    while (1)
    {
        scancode = read_scan_code();
        if ((scancode & 128) == 128)
        {
            // Released
        }
        else
        {
            //if (scancode == 0x1E)

            //vga.print("A pressed");

            //scancode -= 128;
            itoa(hex2dec(&scancode), str);
            vga.print(str);

            //pressed
        }
    }
}