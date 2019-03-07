/**
Timer/counter overflow (interrupt based)

This use case will prepare a timer to trigger an interrupt when the timer overflows. The interrupt is handled by a cutomisable callback function.
We will setup the timer in this mode:
Normal WGM mode (incrementing timer)
Use the system clock as clock source
No prescaling (clock divider set to 1)
Overflow interrupt after 1000 counts. This will be done by setting the top value to 1000.

 */
#include <asf.h>

static void ya_1s(void)
{
	PORTR.OUTTGL=PIN0_bm;	
}

static void counter_init(void)
{
	tc_enable(&TCC0); //TCC0,TCC1,TCD0,TCD1,TCE0  tres tipo cero y dos tipo 1 de 16bits
	//los tipo cero tienen 4 canales cc y los 1 solo 2
	tc_set_overflow_interrupt_callback(&TCC0, ya_1s);//activa la interrupcion por overflow
	//hay otras interrupciones por canal tc_set_cca_interrupt_callback  canal a
	//y su prioridad tc_set_cca_interrupt_level
	
	tc_set_wgm(&TCC0, TC_WG_NORMAL);//Set the desired waveform mode contador nada mas
	tc_write_period(&TCC0, 31250);  //Set the period como es de 16 bis maxima cuenta hasta 2 a la 16
	tc_set_overflow_interrupt_level(&TCC0, TC_INT_LVL_LO); //Set the overflow interrupt level
	sei();
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1024_gc); //When the clock source is set, the timer will start counting

//en 1 seg son 32000000 ciclos entonces con un prescalador de 1024 solo cuenta hasta 31250

}

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	pmic_init();
	sysclk_init();
	counter_init();
	
	while (1)
	{
		
	}

}
