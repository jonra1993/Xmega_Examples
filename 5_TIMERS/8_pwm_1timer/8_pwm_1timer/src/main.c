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


volatile uint16_t ancho[8];
volatile uint16_t valor;
int pot;
uint16_t tempo;

static void dutty(int i, uint16_t a)
{
	ancho[i]=a;
}

static void activar(void)
{
	tempo++;
	PORTR.OUTTGL=PIN0_bm;
	
	if (tempo==ancho[0])
	{
		PORTC.OUTCLR=PIN0_bm;
	}
	if (tempo==ancho[1])
	{
		PORTC.OUTCLR=PIN1_bm;
	}
	if (tempo==ancho[2])
	{
		PORTC.OUTCLR=PIN2_bm;
	}
	if (tempo==ancho[3])
	{
		PORTC.OUTCLR=PIN3_bm;
	}
	if (tempo==ancho[4])
	{
		PORTC.OUTCLR=PIN4_bm;
	}
	if (tempo==ancho[5])
	{
		PORTC.OUTCLR=PIN5_bm;
	}
	if (tempo==ancho[6])
	{
		PORTC.OUTCLR=PIN6_bm;
	}
	if (tempo==ancho[7])
	{
		PORTC.OUTCLR=PIN7_bm;
	}							
	
	if (tempo==100)
	{
		PORTC.OUT=255;
			tempo=-1;
	}
}
static void iniciar_timer_c0(void)
{
	tc_enable(&TCC0);
	tc_set_cca_interrupt_callback(&TCC0, activar);
	tc_set_wgm(&TCC0, TC_WG_NORMAL);
	tc_write_period(&TCC0,4800); //para frecuencia de 1k necsita dar 32000ciclos	
	tc_write_cc(&TCC0,TC_CCA,48);
	tc_enable_cc_channels(&TCC0,TC_CCAEN);
	tc_set_cca_interrupt_level(&TCC0, TC_INT_LVL_HI);
	sei();
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc); //When the clock source is set, the timer will start counting
	
}

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	pmic_init();
	iniciar_timer_c0();
	
	PORTC.DIR=255;
	PORTR.DIRSET=PIN0_bm;
	
	dutty(0,100);
	dutty(1,10);
	dutty(2,20);
	dutty(3,30);
	dutty(4,40);
	dutty(5,50);
	dutty(6,60);
	dutty(7,0);

	while (1)
	{
	
	}
}
