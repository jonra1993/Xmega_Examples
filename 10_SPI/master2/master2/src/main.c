
#include <asf.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


volatile uint8_t tx_byte = 0;
volatile uint8_t rx_byte = 0;

int main (void)
{
	sysclk_init();
	board_init();

    /* Configure GPIO */
    PORTC.DIR = 0B01000000;          // MISO output; MOSI, SCK, SS inputs        ESCLAVO
    PORTD.DIR = 0B10110000;          // MOSI, SCK, SS outputs; MISO input        MASTER
    PORTD.OUTSET = PIN4_bm;       // LE ACTIVA EN 1
    
    /* Configure SPI on PORTC and PORTD */
    SPIC.CTRL = 0B01000000;          // spi slave, spi mode 0, PRESCALADOR DE 4
    SPID.CTRL = 0B01010000;          // spi master, spi mode 0
     	
	PORTA.DIR=0B10;
	PORTA.PIN0CTRL=PORT_OPC_PULLUP_gc;
	
	while (1)
	{
		uint8_t leer=PORTA.IN;
		
		if ((leer&0b01)==0)
		{
			        ///// SPI Master operation /////
			        PORTD.OUTCLR = PIN4_bm;          // assert SS pin (active low)
			        SPID.DATA = 'a';      // increment received data and send (prior int flag auto cleared)
			        while(!(SPID.STATUS & 0x80)); // wait for transmit complete
					rx_byte = SPIC.DATA;          // grab received byte
			        PORTD.OUTSET = PIN4_bm;          // de-assert SS pin
			        
			        tx_byte = SPID.DATA;          // store character received from slave (int flag auto cleared)
			        ////////////////////////////////
			        
			        ////// SPI Slave operation ////
			        SPIC.DATA = rx_byte;          // send back to the master
			        ////////////////////////////////
		}
		
		if (rx_byte=='a')
		{
			PORTA.OUTSET=PIN1_bm;
		}

	}
}