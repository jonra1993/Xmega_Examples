/*
You are a newbie and need help? Here's:
This display has 8 pin (at the time I'm writing this):

TFT side   -------------------- microprocessor
- Vcc       -->     +3V3V(!!!!)
- Gnd       -->     Gnd
- CS        -->     CS pin (3v3 level!)
- RST       -->     connect to a MCU pin or tie to +3V3 or 10K to 3V3 (do NOT leave float!)
- A0        -->     DC or RS pin (3v3 level!)
- SDA       -->     Mosi (3v3 level!)
- SCK       -->     Sclk (3v3 level!)
- LED       -->     Some display need a resistor (see note below)
*/


#pragma once

#include "conf_board.h"
#include <avr/io.h>

#define SPI_PORT PORTD
#define SPI_SS_CS   PIN4_bm
#define SPI_MOSI_SDA PIN5_bm
#define SPI_MISO_A0 PIN6_bm
#define SPI_SCK  PIN7_bm
#define SPI_RST      PIN3_bm

#define SPI SPID


/**
 * set spi speed and settings
 */
void spi_init(void);

/**
 * send spi data
 */
void spi_send(uint8_t data);