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

volatile uint16_t valor;
volatile uint16_t otro;

static void adc_INTERRUPCION(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	switch(ch_mask){
	case ADC_CH0:
		valor=result;
	break;
	case ADC_CH1:
		otro=result;
	break;
	}
}

static void adc_init(void)
{
	irq_initialize_vectors();
	struct adc_config         adc_conf;
	struct adc_channel_config adcch_conf;
	// Initialize configuration structures.
	adc_read_configuration(&ADCA, &adc_conf);
	adcch_read_configuration(&ADCA, ADC_CH0, &adcch_conf);

	/* Configure the ADC module:
	 * - unsigned, 12-bit results
	 * - bandgap (1 V) voltage reference
	 * - 200 kHz maximum clock rate
	 * - manual conversion triggering
	 * - callback function
	 */
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_8,ADC_REF_BANDGAP); //SIGNED VER DATASHEET PARA QUE SEA DESDE CERO
	adc_set_clock_rate(&adc_conf, 20000UL); //se reduce el tiempo por ser freeruning a 5khz
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_FREERUN_SWEEP, 2, 0); //dos adc y freerunning para mejor funcionamiento acaba uno y hacer el otro automaticamente
 	adc_set_callback(&ADCA, &adc_INTERRUPCION);
    adc_write_configuration(&ADCA, &adc_conf);

	adcch_set_interrupt_mode(&adcch_conf, ADCCH_MODE_COMPLETE);
	adcch_enable_interrupt(&adcch_conf);
	/* Configure ADC channel 0:
	 * - interrupt flag set on completed conversion
	 * - interrupts disabled
	 poner en orden como abajo
	 */
	adcch_set_input(&adcch_conf, ADCCH_POS_PIN0, ADCCH_NEG_NONE,1);
	adcch_write_configuration(&ADCA, ADC_CH0, &adcch_conf);
	
	adcch_set_input(&adcch_conf, ADCCH_POS_PIN1, ADCCH_NEG_NONE,1);
	adcch_write_configuration(&ADCA, ADC_CH1, &adcch_conf);
	sei();
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

		board_init();
		sysclk_init();
		conf_serial_com();
		sleepmgr_init(); //no hara nada
		adc_init();
		// Enable the ADC and start the first conversion.
		adc_enable(&ADCA);
		
		PORTC.OUTSET=PIN0_bm;
		PORTR.OUTSET=PIN0_bm;
		

	while (1)
	{
		usart_putchar(USART_SERIAL_D0, 'V');
		usart_putchar(USART_SERIAL_D0, ':');
		usart_putchar(USART_SERIAL_D0, valor);
		usart_putchar(USART_SERIAL_D0, '\n');
		usart_putchar(USART_SERIAL_D0, 'O');		
		usart_putchar(USART_SERIAL_D0, ':');
		usart_putchar(USART_SERIAL_D0, otro);
		usart_putchar(USART_SERIAL_D0, '\n');
		_delay_ms(500);
		
		if (valor<200)
		{
			PORTR.OUTCLR=PIN0_bm;
		}
		else
		{
			PORTR.OUTSET=PIN0_bm;
		}


	}

}
