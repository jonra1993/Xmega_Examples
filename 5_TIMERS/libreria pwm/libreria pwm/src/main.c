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

int prendido;

struct pwm_config pwm_cfg;	    //Define config struct for PWM module:

static void interrupcion(void)
{
	PORTC.OUTTGL=PIN1_bm;	
}

static void conf_pwm(void)
{
	pmic_init();
	sei();
	pwm_init(&pwm_cfg, PWM_TCC0, PWM_CH_A, 60); //Initialize config struct and set up PWM with frequency of 60 Hz.
	//timer c0 y el chanel a osea pin 0	
	pwm_overflow_int_callback(&pwm_cfg, interrupcion); //con int overflow del timer
}

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	sysclk_init();
	conf_pwm();
	pwm_start(&pwm_cfg, 5); // va de 0 a 100 indica el porcentaje
	
	
	while (1)
	{
		prendido=PORTC.IN & 1;
		PORTR.OUT=prendido;  //solo para el pin r0
		
	}

}
