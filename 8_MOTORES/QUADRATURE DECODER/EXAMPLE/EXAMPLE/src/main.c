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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
uint16_t qdec_position, qdec_position_prev = 0;
uint8_t qdec_dir ;

qdec_config_t config;
struct pwm_config pwm_cfg;	

static void qdec_init(void)
{
 //* QDec configuration
 //*   - PA5 - QDPH0
 //*   - PA6 - QDPH90
 //*   - PA7 - QDINDX
	qdec_get_config_defaults(&config);   //TIMER C0 Y Y F C1
	qdec_config_phase_pins(&config, &PORTA, 5, false, 500);
	qdec_config_revolution(&config, 20);
	qdec_config_enable_freq(&config, 1);
	qdec_enabled(&config);
}
ISR(USART_RX_Vect)
{
	usart_putchar(CONF_TEST_USART,usart_getchar(CONF_TEST_USART));
	while (!usart_tx_is_complete(CONF_TEST_USART)) {
	}
	usart_clear_tx_complete(CONF_TEST_USART);
}
static void conf_serial(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};
	
	sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
	usart_set_rx_interrupt_level(CONF_TEST_USART, USART_INT_LVL_LO);	
}

///////////////////////////////////////////////////
//PWM FRENO
static void conf_PWM(void)
{
	pmic_init();
	pwm_init(&pwm_cfg, PWM_TCD0, PWM_CH_A, 100); //Initialize config
	pwm_start(&pwm_cfg, 50); // va de 0 a 100 indica el porcentaje
}
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	
	board_init();
	sysclk_init();
	qdec_init();
	conf_PWM();
	conf_serial();
	irq_initialize_vectors();
	sei();
	
	
	printf("\x0C\n\r-- QDec Example --\n\r");
	printf("-- Compiled: %s %s --\n\r\n\r", __DATE__, __TIME__);
	while (1)
	{
		qdec_position = qdec_get_position(&config);
		qdec_dir = qdec_get_direction(&config);
		
		if (qdec_position_prev != qdec_position)
		 {
			/* New position then display it */
			qdec_position_prev = qdec_position;
			printf("%02u", qdec_position);
			/* display direction */
			if (qdec_dir)
			 {
				printf(" ++");
			 }
		     else
			  {
				printf(" --");
		      }

			/* Display frequency */
			printf(" %5umHz\r\n", qdec_get_frequency(&config));		
		}
	}
	/* Insert application code here, after the board has been initialized. */
}
