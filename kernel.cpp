#include "vga.h"
#include "utils.h"

// This is our kernel's main function
extern "C" void kernel_main()
{ // We're here! Let's initiate the terminal and display a message to show we got here.
    VGA vga;
    // Initiate terminal
    vga.putc(char(176));
    // Display some messages
    vga.print("starting opOSsum\n");

    //vga.setColor(COLOR::LIGHT_GREEN, COLOR::WHITE);

    for (int i = 0; i <= 255; i++)
    {
        char *c;
        itoa(i, c);
        vga.print(c);
        vga.putc(' ');
        vga.putc(char(i));
    }
    vga.print(R"(
                                                                
 @@@@@@  @@@@@@@   @@@@@@   @@@@@@  @@@@@@ @@@  @@@ @@@@@@@@@@  
@@!  @@@ @@!  @@@ @@!  @@@ !@@     !@@     @@!  @@@ @@! @@! @@! 
@!@  !@! @!@@!@!  @!@  !@!  !@@!!   !@@!!  @!@  !@! @!! !!@ @!@ 
!!:  !!! !!:      !!:  !!!     !:!     !:! !!:  !!! !!:     !!: 
 : :. :   :        : :. :  ::.: :  ::.: :   :.:: :   :      :   
                                                                
    )");

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
}
