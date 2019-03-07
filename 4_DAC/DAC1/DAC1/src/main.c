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
#include <compiler.h>
#include <dac.h>

#define RATE_OF_CONVERSION       164462
#define NR_OF_SAMPLES            32

static const uint16_t sine[NR_OF_SAMPLES] = {
	32768, 35325, 37784, 40050, 42036, 43666, 44877, 45623,
	45875, 45623, 44877, 43666, 42036, 40050, 37784, 35325,
	32768, 30211, 27752, 25486, 23500, 21870, 20659, 19913,
	19661, 19913, 20659, 21870, 23500, 25486, 27752, 30211,
};
static void evsys_init(void) //se configura que convierta la dac por evento el overflow del timer
{
	//Use the sysclk service to enable the clock to the event system:
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_EVSYS);
	//Connect the TCC0 overflow event to event channel 3:
	EVSYS.CH3MUX = EVSYS_CHMUX_TCC0_OVF_gc;
}
static void tc_init(void)
{
	//Enable the clock to the DAC trigger timer:
	tc_enable(&TCC0);
	//Configure the DAC trigger timer in normal Waveform Generation mode:
	tc_set_wgm(&TCC0, TC_WG_NORMAL);
	//Configure the DAC trigger timer period to overflow at at the specified rate of conversion in Hz:
	tc_write_period(&TCC0, (sysclk_get_per_hz() / RATE_OF_CONVERSION) - 1);
	//Configure the DAC trigger timer clock source to use the peripheral bus frequency:
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc);
}
static void dac_init(void)
{
	struct dac_config conf; //Config struct for the DAC:
	dac_read_configuration(&DACB, &conf);
	dac_set_conversion_parameters(&conf, DAC_REF_BANDGAP, DAC_ADJ_LEFT);
	dac_set_active_channel(&conf, DAC_CH0, 0);
	dac_set_conversion_trigger(&conf, DAC_CH0, 3);
	#ifdef XMEGA_DAC_VERSION_1
	dac_set_conversion_interval(&conf, 1);
	#endif
	dac_write_configuration(&DACB, &conf);
	dac_enable(&DACB);
}

int main (void)
{
	board_init();
	sysclk_init();
	evsys_init();
	tc_init();
	dac_init();
	uint8_t i = 0;
	while (1)
	{
    dac_wait_for_channel_ready(&DACB, DAC_CH0);
    dac_set_channel_value(&DACB, DAC_CH0, sine[i]);
    i++;
    i %= NR_OF_SAMPLES;		
	}
}
