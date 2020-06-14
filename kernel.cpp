#include "vga.h"
#include "utils.h"

// This is our kernel's main function
extern "C" void kernel_main()
{
    VGA vga;
    vga.print("bootloader asm finished\nstarting kernel\n");
    vga.setColor(COLOR::LIGHT_BLUE, COLOR::WHITE);

    auto test = [&vga]() -> void {
        for (int i = 0; i <= 301; i++)
        {
            for (int j = 0; j <= 15; j++)
            {
                vga.setColor(j | j % 15 << 4);
                vga.update();
                //vga.print("1");
            }
        }
        vga.setColor(COLOR::LIGHT_GREEN, COLOR::BLACK);
        vga.update();
        vga.putc(char(176));
        char cc = char(219);
        vga.print(&cc);

        vga.update();
        for (int i = 0; i <= 255; i++)
        {
            char *c;
            itoa(i, c);
            vga.print(c);
            vga.putc(' ');
            vga.putc(char(i));
        }
    };
    auto line = [&vga](COLOR color, int len) {
        vga.setColor(color, COLOR::BLACK);
        for (int i = 0; i < len; i++)
        {
            vga.putc(char(205));
        }
        vga.update();
    };
    vga.putc('\n');
    line(COLOR::RED, 80);
    vga.print(R"(
 @@@@@@  @@@@@@@   @@@@@@   @@@@@@  @@@@@@ @@@  @@@ @@@@@@@@@@  
@@!  @@@ @@!  @@@ @@!  @@@ !@@     !@@     @@!  @@@ @@! @@! @@! 
@!@  !@! @!@@!@!  @!@  !@!  !@@!!   !@@!!  @!@  !@! @!! !!@ @!@ 
!!:  !!! !!:      !!:  !!!     !:!     !:! !!:  !!! !!:     !!: 
 : :. :   :        : :. :  ::.: :  ::.: :   :.:: :   :      :   
)");
    vga.putc('\n');
    line(COLOR::RED, 80);
    vga.print("\ncolor test\n");
    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j <= 15; j++)
        {
            vga.setColor(i | j << 4);
            vga.putc(char(16));
            vga.putc(char(17));
        }
    }
}