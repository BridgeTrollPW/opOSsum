#include "vga.hpp"
#include "utils.hpp"

// This is our kernel's main function
extern "C" void kernel_main()
{
    VGA vga;
    vga.print("bootloader asm finished\nstarting kernel\n");
    vga.setColor(COLOR::LIGHT_BLUE, COLOR::WHITE);
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