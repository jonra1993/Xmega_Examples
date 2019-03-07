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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "spi_driver.h"


#define NUM_BYTES   2                     /*! \brief Number of test data bytes. */
SPI_Master_t spiMasterC;                  /*! \brief SPI master on PORT C. */
SPI_Slave_t spiSlaveD = {NULL, NULL};     /*! \brief SPI slave on PORT D. */
SPI_DataPacket_t dataPacket;             /*! \brief Data packet. */
const uint8_t sendData[NUM_BYTES + 1] = { 0x55, 0xaa, 0x00 };  /*! \brief Test data to send. */
uint8_t receivedData[NUM_BYTES + 1];      /*! \brief Buffer for test data reception. */

/*! \brief Result of the example test. */
bool success;
/*! \brief Test function.
 *
 *  This function tests the SPI master and slave drivers in interrupt-driven
 *  operation, with a master (on port C) communicating with a slave (on port D).
 *
 *  Hardware setup:
 *
 *    - Connect PC4 to PD4 (SS)
 *    - Connect PC5 to PD5 (MOSI)
 *    - Connect PC6 to PD6 (MISO)
 *    - Connect PC7 to PD7 (SCK)
 *
 *  The driver is tested by transmitting data from the master to the slave.
 *  The slave increments the received data and sends it back. The master reads
 *  the data from the slave and verifies that it equals the data sent + 1.
 *
 *  The first data transaction is initiated by the main routine. When a
 *  transaction has finished, an interrupt will be triggered which will start
 *  new transactions until all bytes have been transceived.
 *
 *  The variable, 'success', will be non-zero when the function reaches the
 *  infinite for-loop if the test was successful.
 *
 *  \note This example uses multilevel interrupts. For more information on how
 *        to use the interrupt controller, refer to application note AVR1305.
 */
int main (void)
{
	sysclk_init();
	board_init();

	/* Init SS pin as output with wired AND and pull-up. */
	PORTC.DIRSET = PIN4_bm;
	PORTC.PIN4CTRL = PORT_OPC_WIREDANDPULL_gc;

	/* Set SS output to high. (No slave addressed). */
	PORTC.OUTSET = PIN4_bm;

	/* Initialize SPI master on port C. */
	SPI_MasterInit(&spiMasterC, &SPIC, &PORTC, false, SPI_MODE_0_gc, SPI_INTLVL_LO_gc, false, SPI_PRESCALER_DIV4_gc);   //reloj/4 =sck

	/* Initialize SPI slave on port D. */
	SPI_SlaveInit(&spiSlaveD, &SPID, &PORTD, false, SPI_MODE_0_gc, SPI_INTLVL_MED_gc);

	/* Enable low and medium level interrupts in the interrupt controller. */
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();

	/* Create data packet (SS to slave by PC4) */
	SPI_MasterCreateDataPacket(&dataPacket, sendData, receivedData, NUM_BYTES + 1, &PORTC, PIN4_bm);

	/* Transmit and receive first data byte. */
	uint8_t status;
	do {
		status = SPI_MasterInterruptTransceivePacket(&spiMasterC, &dataPacket);
	} while (status != SPI_OK);
	
	/* Wait for transmission to complete. */
	while (dataPacket.complete == false) {};

	/* Check that correct data was received. Assume success at first. */
	success = true;
	for (uint8_t i = 0; i < NUM_BYTES; i++) {
		if (receivedData[i + 1] != (uint8_t)(sendData[i] + 1)) {
			success = false;
		}
	}
	while(true) {
		nop();
	}
}

/*! \brief SPI master interrupt service routine.
 *  The interrupt service routines calls one common function,
 *  SPI_MasterInterruptHandler(SPI_Master_t *spi),
 */
ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiMasterC);
}



/*! \brief SPI slave interrupt service routine.
 *  This ISR increments the received data and stores it in the
 *  data register, read to be shifted back by the master.
 *  If more extensive computation is needed, it is recommended
 *  to do this in a function, which is then called by the ISR.
 */
ISR(SPID_INT_vect)
{
	/* Get received data. */
	uint8_t data = SPI_SlaveReadByte(&spiSlaveD);

	/* Increment data. */
	data++;

	/* Send back incremented value. */
	SPI_SlaveWriteByte(&spiSlaveD, data);
}
