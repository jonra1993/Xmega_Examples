
#include <asf.h>
#include "spi_driver.h"
#include <util/delay.h>

#define NUM_BYTES   2                     /*! \brief Number of test data bytes. */
SPI_Slave_t spiSlaveD = {NULL, NULL};     /*! \brief SPI slave on PORT D. */
const uint8_t ref[NUM_BYTES + 1] = { 'i', 120, 'f' };  /*! \brief Test data to send. */
uint8_t receivedData[NUM_BYTES + 1] = {0, 10, 8 };      /*! \brief Buffer for test data reception. */

/*! \brief Test function.
 *    - Connect PD4 (SS)
 *    - Connect PD5 (MOSI)
 *    - Connect PD6 (MISO)
 *    - Connect PD7 (SCK)
*/

uint8_t uno=0;
uint8_t dos=0;
uint8_t tres=0;

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	sysclk_init();
	board_init();
    PORTD.DIR = 0B01000000;          // MISO output; MOSI, SCK, SS inputs
	PORTD.OUTCLR=PIN4_bm;
	/* Initialize SPI slave on port D. */
	SPI_SlaveInit(&spiSlaveD, &SPID, &PORTD, false, SPI_MODE_0_gc, SPI_INTLVL_MED_gc);
	/* Enable low and medium level interrupts in the interrupt controller. */
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();
	PORTA.DIRSET=PIN0_bm;
	PORTA.OUTCLR=PIN0_bm;
	
	PORTA.DIRSET=PIN1_bm;
	PORTA.OUTCLR=PIN1_bm;
	
		
while (1)
{
// 		for (uint8_t i = 1; i <= NUM_BYTES+1; i++) 
// 		{
// 			
// 			if (receivedData[i - 1] != (uint8_t)(ref[i - 1])) {
// 				PORTA.OUTCLR=PIN0_bm;
// 			}
// 			else
// 			{
// 				PORTA.OUTSET=PIN0_bm;
// 			}
// 		}
}
	
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
	if (data=='a')
	{	
		PORTA.OUTSET=PIN0_bm;
	} 
	else if (data=='b')
	{
		PORTA.OUTCLR=PIN0_bm;
	}
	
	//if ((uno==0)&&(dos==0))
	//{
	//	receivedData[0]=data;
	//	uno=1;
	//}
	//if ((uno==1)&&(dos==0))
	//{
	//	receivedData[1]=data;
	//	dos=1;
	//}
	//if ((uno==1)&&(dos==1))
	//{
	//	receivedData[2]=data;
	//	uno=0;
	//	dos=0;
	//}	
	
	/* Send back incremented value. */
	//SPI_SlaveWriteByte(&spiSlaveD, data);
}