#include "io.hpp"
#include "gdt.hpp"
#include "vga.hpp"

#include <stdint.h>
#include <stddef.h>

extern "C" void kernel_main()
{
    gdt_install();
    Screen src;

    src.print("test", 4);

    while (1)
    {
    }
}

/**
 * 
 *     //IDT idt;
    VGA vga;

vga.print(R"(         @@@@@@  @@@@@@@   @@@@@@   @@@@@@  @@@@@@ @@@  @@@ @@@@@@@@@@ 
        @@!  @@@ @@!  @@@ @@!  @@@ !@@     !@@     @@!  @@@ @@! @@! @@!
        @!@  !@! @!@@!@!  @!@  !@!  !@@!!   !@@!!  @!@  !@! @!! !!@ @!@
        !!:  !!! !!:      !!:  !!!     !:!     !:! !!:  !!! !!:     !!:
         : :. :   :        : :. :  ::.: :  ::.: :   :.:: :   :      :  
)");

    unsigned char scancode;
    char *str;
    bool once;
    while (1)
    {
        scancode = read_scan_code();
        if ((scancode & 128) == 128)
        {
            // Released
            once = false;
        }
        else
        {
            //if (scancode == 0x1E)

            //vga.print("A pressed");

            //scancode -= 128;
            //itoa(hex2dec(&scancode), str);
            if (!once)
            {
                vga.putc((int)scancode);
                once = true;
            }

            //pressed
        }
    }


#define KBD_DATA_PORT 0x60

** read_scan_code:
     *  Reads a scan code from the keyboard
     *
     *  @return The scan code (NOT an ASCII character!)
     
unsigned char read_scan_code()
{
    return inb(KBD_DATA_PORT);
}
 * */