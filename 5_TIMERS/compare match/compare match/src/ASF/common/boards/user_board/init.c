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
	PORTR.DIRSET=PIN0_bm;
	PORTC.DIRSET=PIN0_bm;
	
	PORTC.OUTCLR=PIN0_bm;
	PORTR.OUTCLR=PIN0_bm;
}
