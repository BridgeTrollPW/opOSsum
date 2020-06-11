

// This is our kernel's main function
extern "C" void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.

	// Initiate terminal
	term_init();

	// Display some messages
	term_print("starting opOSsum\n");

	for(int i = 0; i <= 255; i++) {
	  term_putc(char(i));
    }
}