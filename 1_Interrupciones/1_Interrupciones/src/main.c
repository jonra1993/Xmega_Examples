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
#define F_CPU 48000000UL //se conf en sysclk para esa frecuencia
#include <asf.h>
#include <util/delay.h>
#include <interrupt.h>

#define LEDPORT PORTR
#define LEDPIN PIN0_bm

volatile int i,a;
int sec1[14]={1,2,4,8,16,32,64,128,64,32,16,8,4,2};
int sec2[5]={0b10000001,0b01000010,0b00100100,0b00011000,0};
	
volatile int filtro;	
	
ISR(PORTA_INT0_vect)  //todos los puertos tienen 2 int 0 y 1
{
	_delay_ms(20);
	a=0;
	filtro=(PORTA.IN & 0b00000001);
	if (filtro==1)
	{
		LEDPORT.OUTTGL=LEDPIN;
		PORTC.OUT=sec1[i];
		i++;
		if (i==14) i=0;
		
	}
}


ISR(PORTA_INT1_vect)
{
	_delay_ms(20);
	i=0;
	filtro=(PORTA.IN & 0b00000010);
	if (filtro==2)
	{
		LEDPORT.OUTTGL=LEDPIN;
		PORTC.OUT=sec2[a];
		a++;
		if (a==5) a=0;
		
	}
}


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	
	PORTC.DIR=255;  //PUERTO C COMO SALIDA
	LEDPORT.DIRSET=LEDPIN;   //LED DE LA PLACA COMO SALIDA
	LEDPORT.OUTSET=LEDPIN; //LE ENCIENDE
	
	//INTERRUPCION PROGRAMMABLE MULTILEVEL INTERRUPTO CONTROLLER
	//PORTA.DIRCLR=PIN0_bm;
	//PORTA.DIRCLR=PIN1_bm;
	PORTA.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_RISING_gc;  //SE ACTIVA EL FLANCO DE SUBIDA EN EL PIN A0
	PORTA.PIN1CTRL=PORT_ISC_RISING_gc; 

	PORTA.INT1MASK =0B00000010;
	//PORTA.INTCTRL |=PORT_INT1LVL_MED_gc;  //NIVEL ALTO @OJO PONER COMO OR SINO LE APGA AL OTRO@

	PORTA.INT0MASK =0B00000001; //elige a c0 como fuente de interrupcion 0
	PORTA.INTCTRL |=PORT_INT0LVL_LO_gc|PORT_INT1LVL_MED_gc;   //SE INDICA EL NIVEL DE IMPORTANCIA EN MEDIO

		
	//SE PUDO PONER CTRL=0B101;
	PMIC.CTRL |= PMIC_MEDLVLEN_bm; 
	PMIC.CTRL |= PMIC_LOLVLEN_bm;  //UN 1 EN EL REGISTRO HABILITA EL NIVEL MEDIO Y ALTO
	sei(); //habilita int globales
	
	i=0;
	while (1)
	{
		
	}
}

