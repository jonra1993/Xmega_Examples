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
#define RATE_OF_CONVERSION       500
#define OUTPUT_DAC              DACB

static void tc_init(void)
{
	tc_enable(&TCC0);
	tc_set_wgm(&TCC0, TC_WG_NORMAL);
	tc_write_period(&TCC0, (sysclk_get_per_hz() / RATE_OF_CONVERSION) - 1);
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc);
}
static void dac_init(void)
{
	struct dac_config conf;
	dac_read_configuration(&OUTPUT_DAC, &conf);
	dac_set_conversion_parameters(&conf, DAC_REF_AVCC, DAC_ADJ_RIGHT);
	dac_set_active_channel(&conf, DAC_CH0 | DAC_CH1, 0);
	#ifdef XMEGA_DAC_VERSION_1
	dac_set_conversion_interval(&conf, 10);
	dac_set_refresh_interval(&conf, 20);
	#endif
	dac_write_configuration(&OUTPUT_DAC, &conf);
	dac_enable(&OUTPUT_DAC);
}




int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	tc_init();
	dac_init();
	
	while (1)
	{
		while (!(tc_is_overflow(&TCC0))) {}; //Wait for channels to get ready for new values, by waiting for the sample timer to overflow and then clearing the flag:
		tc_clear_overflow(&TCC0);
		//Set the value of channel 0 to 10% and the other to 90% of maximum:
		dac_set_channel_value(&OUTPUT_DAC, DAC_CH0, 410);
		dac_set_channel_value(&OUTPUT_DAC, DAC_CH1, 3686);
		while (!(tc_is_overflow(&TCC0))) {}; //Wait for channels to get ready for new values, by waiting for the sample timer to overflow and then clearing the flag:
		tc_clear_overflow(&TCC0);
		//Set the value of channel 0 to 10% and the other to 90% of maximum:
		dac_set_channel_value(&OUTPUT_DAC, DAC_CH0, 3686);
		dac_set_channel_value(&OUTPUT_DAC, DAC_CH1, 410);
	}

	// Insert application code here, after the board has been initialized.
}
