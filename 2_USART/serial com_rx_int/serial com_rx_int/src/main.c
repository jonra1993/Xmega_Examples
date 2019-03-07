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
#include <conf_usart_serial.h>
#include <util/delay.h>

volatile uint8_t received_byte;
uint8_t encoded_message[] = {
	0xF2, 0xF5, 0xAB, 0x97, 0x96, 0x8C, 0xDF, 0x96, 0x91, 0xDF,
	0x9E, 0x91, 0xDF, 0x9A, 0x91, 0x9C, 0x90, 0x9B, 0x9A, 0x9B,
	0xDF, 0x92, 0x9A, 0x8C, 0x8C, 0x9E, 0x98, 0x9A, 0xDF, 0x8C,
	0x9A, 0x91, 0x8B, 0xDF, 0x99, 0x8D, 0x90, 0x92,
	0xDF, 0xA7, 0xB2, 0xBA, 0xB8, 0xBE, 0xDF, 0xAA,
	0xAC, 0xBE, 0xAD, 0xAB, 0xDE
};
uint8_t i;
uint8_t tx_buf[] = "\n\rHello AVR Jonathan ! : ";
uint8_t tx_length = 25;

ISR(USART_RX_Vect)
{
	usart_putchar(USART_SERIAL_E0,
	usart_getchar(USART_SERIAL_E0));
	while (!usart_tx_is_complete(USART_SERIAL_E0)) {
	}
	usart_clear_tx_complete(USART_SERIAL_E0);
}


int main (void)
{
	
	
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	pmic_init();
	sei();
	
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	
	sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm);
	usart_init_rs232(USART_SERIAL_E0, &USART_SERIAL_OPTIONS);
	usart_set_rx_interrupt_level(USART_SERIAL_E0, USART_INT_LVL_LO);


	/* Send "message header" */
	for (i = 0; i < sizeof(encoded_message); i++) {
		usart_putchar(USART_SERIAL_E0, encoded_message[i]);
		while (!usart_tx_is_complete(USART_SERIAL_E0)) {
		}
		usart_clear_tx_complete(USART_SERIAL_E0);
	}
	
	
	
	while (1)
	{


	}

	
}
