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

static uint16_t tempsense;
static volatile uint16_t last_temperature;

static void adc_handler(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	uint32_t temperature;

	/* Compute current temperature in kelvin, based on the factory
	 * calibration measurement of the temperature sensor. The calibration
	 * has been done at 85 degrees Celsius, which corresponds to 358 kelvin.
	 */
	temperature = (uint32_t)result * 358;
	temperature /= tempsense;

	// Store temperature in global variable.
	last_temperature = temperature & 0xffff;

	// Start next conversion.
	adc_start_conversion(adc, ch_mask);
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
	struct adc_config         adc_conf;
	struct adc_channel_config adcch_conf;
	board_init();
	sysclk_init();
	sleepmgr_init();
	irq_initialize_vectors();
	sei();
	// Initialize configuration structures.
	adc_read_configuration(&ADCA, &adc_conf);
	adcch_read_configuration(&ADCA, ADC_CH0, &adcch_conf);
	/* Configure the ADC module:
	 * - unsigned, 12-bit results
	 * - bandgap (1 V) voltage reference
	 * - 200 kHz maximum clock rate
	 * - manual conversion triggering
	 * - temperature sensor enabled
	 * - callback function
	 */
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_OFF, ADC_RES_12,
			ADC_REF_BANDGAP);
	adc_set_clock_rate(&adc_conf, 200000UL);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	adc_enable_internal_input(&adc_conf, ADC_INT_TEMPSENSE);

	adc_write_configuration(&ADCA, &adc_conf);
	adc_set_callback(&ADCA, &adc_handler);
	/* Configure ADC channel 0:
	 * - single-ended measurement from temperature sensor
	 * - interrupt flag set on completed conversion
	 * - interrupts disabled
	 */
	adcch_set_input(&adcch_conf, ADCCH_POS_TEMPSENSE, ADCCH_NEG_NONE,
			1);
	adcch_set_interrupt_mode(&adcch_conf, ADCCH_MODE_COMPLETE);
	adcch_enable_interrupt(&adcch_conf);

	adcch_write_configuration(&ADCA, ADC_CH0, &adcch_conf);

	// Get measurement for 85 degrees C (358 kelvin) from calibration data.
	tempsense = adc_get_calibration_data(ADC_CAL_TEMPSENSE);

	// Enable the ADC and start the first conversion.
	adc_enable(&ADCA);
	adc_start_conversion(&ADCA, ADC_CH0);
	
	conf_serial_com();
	do {
		// Sleep until ADC interrupt triggers.
		//last_temperature=48;
		usart_putchar(USART_SERIAL_D0, last_temperature);
		usart_putchar(USART_SERIAL_D0, '\n');
		usart_putchar(USART_SERIAL_D0, 'J');
		usart_putchar(USART_SERIAL_D0, '\n');
		_delay_ms(10);
		
	} while (1);	
}
