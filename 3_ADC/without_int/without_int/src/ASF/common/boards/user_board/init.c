/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	PORTD.DIRSET = PIN3_bm; //TX pin as output
	PORTD.OUTSET = PIN3_bm; //Let's make Pde as TX
	

	PORTD.DIRCLR = PIN2_bm; //PC6 as RX entrada
	PORTD.OUTCLR = PIN2_bm; //en cero
	
	PORTC.DIRSET= PIN0_bm;
	PORTC.OUTCLR=PIN0_bm;
	
	PORTA.DIRCLR = PIN0_bm;
	
	PORTR.DIRSET=PIN0_bm;
	PORTR.OUTSET=PIN0_bm;	
}
