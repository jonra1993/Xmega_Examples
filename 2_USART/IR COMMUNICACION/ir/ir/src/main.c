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

#include "avr_compiler.h"
#include "usart_driver.h"
#include "IR_driver.h"

#include <util/delay.h>

/*! Define that selects the Usart used in example. */
#define Objeto_IR USARTD0


/*! Success variable, used to test driver. */
bool success;


/*! \brief Example application.
 *
 *  Example application. This example configures USARTC0 for with the parameters:
 *      - 8 bit character size
 *      - No parity
 *      - 1 stop bit
 *      - 9600 Baud
 *
 *  This function then sends the values 0-255 and tests if the received data is
 *  equal to the sent data. The code can be tested by connecting PC3 to PC2. If
 *  the variable 'success' is true at the end of the function, the values
 *  have been successfully sent and received.
 */
int main(void)
{

	/* Variable used to send and receive data. */
	uint8_t sendData;
	uint8_t receivedData;

	/* This PORT setting is only valid to USARTC0 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PIN3 (TXD0) as output. */
	PORTD.DIRSET   = PIN3_bm;
	/* PC2 (RXD0) as input. */
	PORTD.DIRCLR   = PIN2_bm;
	
	//led
	PORTR.DIRSET= PIN0_bm;

	/* USARTC0, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(&Objeto_IR, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, false);

	/* Set Baud rate to 9600 bps:
	 * Use the default I/O clock frequency that is 2 MHz.
	 * Do not use the baud rate scale factor
	 *
	 * Baud rate select = (1/(16*(((I/O clock frequency)/Baud rate)-1)
	 *                 = 12
	 */
	USART_Baudrate_Set(&Objeto_IR, 12 , 0);

	/* Set USARTD0 in IrDA mode.*/
	USART_SetMode(&Objeto_IR, USART_CMODE_IRDA_gc);

	/* If using another Pulse Length than the standard 3/16 use the functions
	 * shown below. */
	/*
	IRCOM_TXSetPulseLength(254);
	IRCOM_RXSetPulseLength(254);
	*/

	/* Enable both RX and TX. */
	USART_Rx_Enable(&Objeto_IR);
	USART_Tx_Enable(&Objeto_IR);


	/* Assume that everything is OK. */
	success = true;
	/* Send data from 255 down to 0*/
	sendData = 255;
	while(sendData) {
	    /* Send one char. */
		do{
		/* Wait until it is possible to put data into TX data register.
		 * NOTE: If TXDataRegister never becomes empty this will be a DEADLOCK. */
		}while(!USART_IsTXDataRegisterEmpty(&Objeto_IR));
		USART_PutChar(&Objeto_IR, sendData);

		uint16_t timeout = 1000;
		/* Receive one char. */
		do{
		/* Wait until data received or a timeout.*/
		timeout--;
		}while(!USART_IsRXComplete(&Objeto_IR) && timeout!=0);
		receivedData = USART_GetChar(&Objeto_IR);

		/* Check the received data. */
		if (receivedData != sendData){
			success = false;
		}
		sendData--;
	}

	/* Disable both RX and TX. */
	USART_Rx_Disable(&Objeto_IR);
	USART_Tx_Disable(&Objeto_IR);

	/* If success the program ends up inside the if statement.*/
	if(success){
		PORTR.OUTSET=PIN0_bm;
		while(true);
	}
	else{
	  	while(true){
			  PORTR.OUTTGL=PIN0_bm;
			  _delay_ms(200);
		  }
	}
}
