

#include <asf.h>
#include "spi_driver.h"
#include <util/delay.h>

#define NUM_BYTES   2                     /*! \brief Number of test data bytes. */
SPI_Master_t spiMasterD;                  /*! \brief SPI master on PORT C. */
SPI_DataPacket_t dataPacket;             /*! \brief Data packet. */
const uint8_t sendData[NUM_BYTES + 1] = { 'i', 120, 'f'};  /*! \brief Test data to send. */
uint8_t receivedData[NUM_BYTES + 1];      /*! \brief Buffer for test data reception. */
bool success;
/*  master (on port D)
	 - Connect PD4 (SS)
*    - Connect PD5 (MOSI)
*    - Connect PD6 (MISO)
*    - Connect PD7 (SCK)
*/

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	/* Init SS pin as input with wired AND and pull-up. */
	PORTD.DIRCLR = PIN4_bm;
	PORTD.PIN4CTRL = PORT_OPC_PULLUP_gc;
	
	PORTD.DIRCLR=PIN6_bm;
	PORTD.DIRSET|=PIN5_bm|PIN7_bm;
	PORTD.OUTSET=PIN5_bm;
	PORTD.OUTSET=PIN7_bm;
	
	/* Initialize SPI master on port D. */
	SPI_MasterInit(&spiMasterD, &SPID, &PORTD, false, SPI_MODE_0_gc, SPI_INTLVL_LO_gc, false, SPI_PRESCALER_DIV4_gc);   //reloj/4 =sck
	/* Enable low and medium level interrupts in the interrupt controller. */
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();

	/* Create data packet (SS to slave by PD4) */
	SPI_MasterCreateDataPacket(&dataPacket, sendData, receivedData, NUM_BYTES + 1, &PORTD, PIN4_bm);
	
	PORTA.DIRCLR=PIN0_bm;
	PORTA.PIN0CTRL=PORT_OPC_PULLUP_gc;
	
	PORTA.DIRSET=PIN1_bm;
	PORTA.OUTCLR=PIN1_bm;
	uint8_t tempo=1;
	_delay_ms(1500);
	while(true)
 {
	tempo=PORTA.IN & 0b1;
	
	if (tempo==0)
	{		
		   PORTA.OUTSET=PIN1_bm;
			/* Transmit and receive first data byte. */
			//SPI_MasterInterruptTransceivePacket(&spiMasterD, &dataPacket);
			 SPI_MasterTransceiveByte(&spiMasterD, 'a');
			//uint8_t status;
			//do {
			//	status = SPI_MasterInterruptTransceivePacket(&spiMasterD, &dataPacket);
			//} while (status != SPI_OK);
			
			/* Wait for transmission to complete. */
			//while (dataPacket.complete == false) {};
	}
	else
	{
		PORTA.OUTCLR=PIN1_bm;
		//SPI_MasterTransceiveByte(&spiMasterD, 'b');
	}
	
	
 }		
}

/*! \brief SPI master interrupt service routine.
 *  The interrupt service routines calls one common function,
 *  SPI_MasterInterruptHandler(SPI_Master_t *spi),
 */
ISR(SPID_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterD);
}