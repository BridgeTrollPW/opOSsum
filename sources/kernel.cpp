#include "io.hpp"
#include "gdt.hpp"
#include "vga.hpp"

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

int convert(char num[])
{
    int len = strlen(num);
    int base = 1;
    int temp = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            temp += (num[i] - 48) * base;
            base = base * 16;
        }
        else if (num[i] >= 'A' && num[i] <= 'F')
        {
            temp += (num[i] - 55) * base;
            base = base * 16;
        }
    }
    return temp;
}

extern "C" void kernel_main()
{
    gdt_install();
    Screen src;
    src.clear();
    src.printf("kernel_main called from x86 bootloader assembly\n");
    src.printf("Global Descriptor Table loaded\n");
    src.printf("VGA Text Mode loaded\n");

    src.setColor(COLOR::LIGHT_RED, COLOR::BLACK);
    src.printf(R"(         @@@@@@  @@@@@@@   @@@@@@   @@@@@@  @@@@@@ @@@  @@@ @@@@@@@@@@ 
        @@!  @@@ @@!  @@@ @@!  @@@ !@@     !@@     @@!  @@@ @@! @@! @@!
        @!@  !@! @!@@!@!  @!@  !@!  !@@!!   !@@!!  @!@  !@! @!! !!@ @!@
        !!:  !!! !!:      !!:  !!!     !:!     !:! !!:  !!! !!:     !!:
         : :. :   :        : :. :  ::.: :  ::.: :   :.:: :   :      :  
)");
    src.setColor(COLOR::WHITE, COLOR::BLACK);
    src.printf("Kernel is starting infinite main loop\n");
    unsigned char scancode;
    bool once;
    while (1)
    {
        scancode = read_scan_code();
        if ((scancode & 128) == 128)
        {
            //released
            once = false;
        }
        else
        {
            //pressed
            //if (scancode == 0x1E)

            //vga.print("A pressed");

            //scancode -= 128;
            //itoa(hex2dec(&scancode), str);
            if (!once)
            {
                src.putchar(char(convert((char *)0x1E)));
                once = true;
            }
        }
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