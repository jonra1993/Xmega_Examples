/*

	Demo of glcd library with AVR8 microcontroller
	
	Tested on a custom made PCB (intended for another project)

	See ../README.md for connection details

*/

#include <avr/io.h>
#include "glcd.h"

/* Function prototypes */
static void setup(void);

static void setup(void)
{
	/* Set up glcd, also sets up SPI and relevent GPIO pins */
	glcd_init();
	
	/* Backlight pin PL3, set as output, set high for 100% output */
	DDRL |= (1<<3);
	PORTL |= (1<<3);
}

int main(void)
{
	setup();
	
	while(1) {
		//glcd_test_circles();
		glcd_test_counter_and_graph();
		//glcd_test_text_up_down();
		//glcd_test_tiny_text();
		//glcd_test_hello_world();
		//glcd_test_rectangles();
		//glcd_test_scrolling_graph();
		//glcd_test_bitmap_128x64();
	}
	
	return 0;
}