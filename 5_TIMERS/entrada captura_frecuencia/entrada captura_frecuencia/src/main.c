/**
 * The example will configure one of the device TC modules in frequency capture
 * mode. The event system is configured to trigger a capture when switch
 * 0 is pressed and released. The resulting value (the interval between press
 * and release) is displayed on the leds. Only the lower 8 bits are displayed.
 *
 * The TC is setup to use a 1000Hz resolution clock and a 32767
 */
#include <asf.h>
/* Example specific defines, please see the example documentation for details */
#define EXAMPLE_TC                       TCC0
#define LEDPORT                          PORTR
#define SWITCHPORT                       PORTA
#define CANAL_EVENTO_PIN0      EVSYS_CHMUX_PORTA_PIN0_gc;

#define TIMER_EXAMPLE_RESOLUTION 1000
#define TIMER_EXAMPLE_PERIOD     0x7fff
#define TIMER_PORT_LED           TCE0



static void cca_callback(void) 
{
	uint16_t cca_capture = tc_read_cc(&EXAMPLE_TC, TC_CCA);
	usart_putchar(USART_SERIAL_D0, 'V');
	usart_putchar(USART_SERIAL_D0, cca_capture);
	PORTR.OUTTGL=PIN0_bm;
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
	
}

int main (void)
{

	// Insert system clock initialization code here (sysclk_init()).
	LEDPORT.DIRSET=PIN0_bm;
	PORTA.DIRCLR=PIN0_bm;
	PORTA.PIN0CTRL=PORT_ISC_BOTHEDGES_gc | PORT_OPC_TOTEM_gc;
	board_init();
	
	conf_serial_com();
	
	/* Setup pin0 (sw0) as input to event system channel 0 */
	EVSYS_CH0MUX = CANAL_EVENTO_PIN0;	
	/* Enable clock to event sys */
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_EVSYS);	
	/* Set resolution */
	tc_set_resolution(&EXAMPLE_TC, TIMER_EXAMPLE_RESOLUTION);
	/* Set period */
	tc_write_period(&EXAMPLE_TC, TIMER_EXAMPLE_PERIOD);
	/* Enable capture channels */
	tc_enable_cc_channels(&EXAMPLE_TC, TC0_CCAEN_bm);
	/* Clear timer interrupts */
	tc_clear_cc_interrupt(&EXAMPLE_TC, TC_CCA);	
	/* Do capture on event channel 0 (sw0) */
	tc_set_input_capture(&EXAMPLE_TC, TC_EVSEL_CH0_gc, TC_EVACT_FRW_gc);
	/* Register callback for interrupt */
	tc_set_cca_interrupt_callback(&EXAMPLE_TC, &cca_callback);
	/* Enable pmic module */
	pmic_init();		
	/* Enable CCA interrupt at level low */
	tc_set_cca_interrupt_level(&EXAMPLE_TC, TC_CCAINTLVL_LO_gc);
	pmic_enable_level(PMIC_LOLVLEN_bm);
	/* Enable clock to timer */
	tc_enable(&EXAMPLE_TC);
	/* Enable global interrupts */
	sei();	
	


	while (1)
	{
	}

	
}
