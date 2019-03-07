
#include "spi.h"

/**
 * set spi speed and settings
 */
void spi_init(void) {

	SPI_PORT.DIRSET  = (SPI_MOSI_SDA) |( SPI_SCK) | (SPI_SS_CS)|(SPI_RST);
	SPI_PORT.DIRCLR  = SPI_MISO_A0;
    SPI_PORT.OUTSET = (SPI_MOSI_SDA) | (SPI_SS_CS)|(SPI_RST);	
	SPI_PORT.OUTCLR= SPI_MISO_A0;
	SPI_PORT.OUTCLR= SPI_SCK;
		
	SPI.CTRL =  SPI_ENABLE_bm|SPI_MASTER_bm;       // spi master, spi mode 0      f/4  8mhz
}


/**
 * send spi data
 */
void spi_send(unsigned char data) {
	 SPI.DATA = data;//move data into spdr
	 while(!(SPI.STATUS & 0x80));//wait till the transmission is finished
}
