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

float counter;

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	LcdInit();
	
	//LcdGoto(0,0);
	//Lcd(" XMEGA Jonathan");                 // display the text
	
	
         	CustChar(0,"\x16\x17\x05\x02\x19\x09\x0E\x07");   //es el 8
			CustChar(1,"\x07\x0F\x0E\x16\x14\x16\x10\x08");
			CustChar(2,"\x1C\x1F\x0C\x0A\x0A\x01\x0D\x06");
			CustChar(3,"\x0D\x17\x14\x08\x13\x12\x0C\x1C");
			CustChar(4,"\x00\x00\x04\x02\x1F\x02\x04\x00"); //flecha
			CustChar(5,"\x00\x0E\x0A\x1F\x1B\x1F\x1F\x00"); //candado
			CustChar(6,"\x00\x00\x0A\x15\x11\x0A\x04\x00"); //corazon
			CustChar(7,"\x00\x0A\x0A\x0A\x00\x11\x0E\x00"); //cara feliz
			
			//SendString(">> 2\xeb\x31\x36 chars <<", 1, 0);     // plain string
			//SendString("userdef:\x08\x01\x02\x03\x04\x05\x06\x07", 2, 0);     // plain string
			//mario
			SendString("\x01\x02", 1, 0);	
			SendString("\x03\x08", 2, 0);	
	while (1)
	{
// 		
// // 		for (int i=0; i<9;i++)
// // 		{
// // 			SendString("\x06", 1, 5);
// // 			if (i==5)
// // 			{
// // 				i=6;
// // 				SendString("\x05", 1, 8);
// // 			}
// // 			SendString("\x04", 1, i);
// // 			_delay_ms(50);
// // 			LcdClear(); 
// 		}

        if(!(PORTD.IN & PIN5_bm))   // if FLIP pressed
		 { 
			_delay_ms(20);       
	        counter=-12732.4123;                      // increment the counter
	        LcdClear();                     // clear the display
			Lcd1;
			Lcd(" XMEGA Jonathan");
	        LcdGoto(6,1);                           // posicion (0,1)
	        SendFloat(counter,2,1);                // display the number
     
			}   
			
			
      	
	}
		
}
