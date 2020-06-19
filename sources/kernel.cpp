#include "io.hpp"
#include "gdt.hpp"
#include "vga.hpp"
#include "memory.hpp"
#include "ps2keyboard.hpp"

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
    gdt_install();
    Screen src;
    src.clear();
    src.printf("kernel_main called from x86 bootloader assembly\n");
    src.printf("Global Descriptor Table loaded\n");
    src.printf("VGA Text Mode loaded\n");
    KeyCodes keyCodes;
    src.printf("Initialized PS/2 Scancodes <-> ASCII\n");

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
            //key released
            once = false;
        }
        else
        {
            //key pressed
            if (!once)
            {
                char key = keyCodes.get(scancode);
                switch (key)
                {
                case 'enter':
                    src.putchar('\n');
                    break;

                default:
                    src.putchar(key);
                    break;
                }

                once = true;
            }
        }
    }
}