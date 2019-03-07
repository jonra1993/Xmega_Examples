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
uint8_t recibido;

static void conf_timer (void)
{
	tc_enable(&TCC0);
	//! TC in single slope PWM mode
	tc_set_wgm(&TCC0, TC_WG_SS);
	//para frecuencia ver datasheet  se calculo para 2khz
	tc_write_period(&TCE0, 15999);// to change the PWM frequency
	
	tc_write_cc(&TCC0, TC_CCA, 15000); //Use tc_write_cc() to change the duty cycle of the PWM signal
	tc_write_cc(&TCC0, TC_CCB, 10000); //Use tc_write_cc() to change the duty cycle of the PWM signal
	tc_write_cc(&TCC0, TC_CCC, 8000); //Use tc_write_cc() to change the duty cycle of the PWM signal
	tc_write_cc(&TCC0, TC_CCD, 200); //Use tc_write_cc() to change the duty cycle of the PWM signal
	tc_enable_cc_channels(&TCC0,(TC_CCAEN | TC_CCBEN | TC_CCCEN | TC_CCDEN));
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc);
}
static void conf_serial_com(void)
{
	pmic_init();
	sei();
	//conf serial comunication
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm);
	usart_init_rs232(USART_SERIAL_D0, &USART_SERIAL_OPTIONS);
	usart_set_rx_interrupt_level(USART_SERIAL_D0, USART_INT_LVL_LO);	
	

	
}
ISR(USART_RX_Vect)
{
	
	recibido=usart_getchar(USART_SERIAL_D0);
	tc_write_cc(&TCC0, TC_CCA, recibido*62);
	
	usart_putchar(USART_SERIAL_D0,recibido);
	while (!usart_tx_is_complete(USART_SERIAL_D0)) {
	}
	usart_clear_tx_complete(USART_SERIAL_D0);	
	
}


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init(); //PIN C0,1,2,3 COMO SALIDA YA QUE ES EL OC0A
	sysclk_init();
	conf_timer();
	conf_serial_com();

	
	bool leer;
	
	while (1)
	{
		
		leer=PORTC.IN & 0b0000001;
		leer=leer;
		PORTR.OUT=leer;
	}

	// Insert application code here, after the board has been initialized.
}
