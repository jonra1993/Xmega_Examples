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

static void compare_match_a(void)
{
	PORTC.OUTTGL=PIN0_bm;
}
static void compare_match_b(void)
{
	PORTR.OUTTGL=PIN0_bm; 
}

static void counter_init(void)
{
 tc_enable(&TCC0);
 tc_set_cca_interrupt_callback(&TCC0,compare_match_a);
 tc_set_ccb_interrupt_callback(&TCC0, compare_match_b);
 tc_set_wgm(&TCC0, TC_WG_NORMAL);
 tc_write_period(&TCC0,62500); 
 tc_write_cc(&TCC0, TC_CCA, 31250);  //1s
 tc_write_cc(&TCC0, TC_CCB, 62500); //medio seg
 tc_enable_cc_channels(&TCC0,(TC_CCAEN | TC_CCBEN));
 tc_set_cca_interrupt_level(&TCC0, TC_INT_LVL_LO);
 tc_set_ccb_interrupt_level(&TCC0, TC_INT_LVL_MED);  //el b tiene mas prioridad
 //tiene cuatro canales a,b,c y d por ser tipo cero
 sei();
 tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1024_gc); //When the clock source is set, the timer will start counting
}

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	
	board_init();
	sysclk_init();
	pmic_init();
	counter_init();
	
	while (1)
	{
	}
	
}
