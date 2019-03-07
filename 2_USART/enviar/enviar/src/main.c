/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	
	sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm);
	usart_init_rs232(USART_SERIAL_E0, &USART_SERIAL_OPTIONS);
	
	while (1)
	{
		usart_putchar(USART_SERIAL_E0, 128);	 //envia
	}

	
}
