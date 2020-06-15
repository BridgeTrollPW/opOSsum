#include "vga.hpp"
#include "utils.hpp"

uint16_t gdt_desc;
int x = 205;
const char *something = (char *)&x;
// This is our kernel's main function
extern "C" void kernel_main()
{
    __asm__ __volatile__("cli");
    __asm__ __volatile__("lgdt (gdt_desc)");
    __asm__ __volatile__("sti");

    VGA vga;
    vga.print("bootloader asm finished\nstarting kernel\n");
    vga.print("Leberwuast ist ein Spast!\n");
    vga.setColor(COLOR::LIGHT_BLUE, COLOR::WHITE);
    auto line = [&vga](COLOR color, int len) {
        vga.setColor(color, COLOR::BLACK);
        for (int i = 0; i < len; i++)
        {
            vga.print(something);
        }
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