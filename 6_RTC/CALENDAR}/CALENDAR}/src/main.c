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

#define LED_PORT PORTC
uint16_t time;
uint32_t timestamp;
uint16_t tecla;

struct calendar_date fecha_actual = {
	.second = 0,
	.minute = 53,
	.hour = 19,
	.date = 19,
	.month = 9,
	.year = 2015
};
static void enviar_fecha(void)
{
	time=rtc_get_time();
	switch (tecla)
	{
	case 1:
	usart_putchar(USART_SERIAL_D0,time);
		break;
	case 2:
	usart_putchar(USART_SERIAL_D0,fecha_actual.hour );
	break;
	case 3:
	usart_putchar(USART_SERIAL_D0,fecha_actual.minute);
	break;
	case 4:
	usart_putchar(USART_SERIAL_D0,fecha_actual.second);
	break;
	case 5:
	usart_putchar(USART_SERIAL_D0,fecha_actual.year );
	break;
	case 6:
	usart_putchar(USART_SERIAL_D0,fecha_actual.month);
	break;
	case 7:
	usart_putchar(USART_SERIAL_D0,fecha_actual.date);
	break;			
	case 8:
	usart_putchar(USART_SERIAL_D0,fecha_actual.dayofweek);
	break;					
	}

	
}
ISR(USART_RX_Vect)
{
	tecla=usart_getchar(USART_SERIAL_D0);
	enviar_fecha();
	while (!usart_tx_is_complete(USART_SERIAL_D0)) {
	}
	usart_clear_tx_complete(USART_SERIAL_D0);
}



static void alarm(uint32_t time)
{

	calendar_add_second_to_date(&fecha_actual);
	PORTR.OUTTGL=PIN0_bm;
	uint8_t bcd;

	/* Since the current time will give alarm when rolling over to
	 * next time unit, we just call with that one.
	 * This is safe to here since it's called from a time unit roll
	 * over.
	 */
	//rtc_set_alarm(time);
    rtc_set_alarm(time);
	// Extract last two digits from time, and put them in bcd
	bcd = time % 10;
	time -= bcd;
	time /= 10;
	bcd = bcd | ((time % 10) << 4);

	// LEDS on xplain are active low, so invert the output
	
	
	LED_PORT.OUT = bcd;
}

static void conf_serial_com(void)
{
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


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	pmic_init();
	board_init();
	sysclk_init();
	sleepmgr_init();
	
	rtc_init();
	rtc_set_callback(alarm);
	sei();
	/* We just initialized the counter so an alarm should trigger on next
	 * time unit roll over.
	 */
	//Set the alarm to trigger on next time unit roll over:
	rtc_set_alarm_relative(0);
	conf_serial_com();
	
	while (true)
	{
		
		enviar_fecha();
		
	}
}
