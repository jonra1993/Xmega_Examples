
#include <asf.h>
#include <conf_usart_serial.h>
volatile uint8_t received_byte=0;

int main (void)
{
	sysclk_init();
	board_init();
	
	PORTD.OUTSET = PIN3_bm; //Let's  TX
	PORTD.DIRSET = PIN3_bm; //TX pin as output

	PORTD.OUTCLR = PIN2_bm;
	PORTD.DIRCLR = PIN2_bm; //PC6 as RX
	
	PORTD.DIRSET = PIN1_bm;  //PC6 as xck   MASTER

	PORTR.DIRSET=PIN1_bm;
	PORTR.OUTSET=PIN1_bm;
	
	 static usart_rs232_options_t USART_SERIAL_OPTIONS_D0 = {
		 .baudrate = 2000000,
		 .charlength = USART_CHSIZE_8BIT_gc,
		 .paritytype = USART_PMODE_DISABLED_gc,
		 .stopbits = false
	 };
	 sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm); 
	 usart_init_rs232(&USARTD0,&USART_SERIAL_OPTIONS_D0);
	 usart_set_mode(&USARTD0, USART_CMODE_SYNCHRONOUS_gc);  //MODO SINCRONICO
	 usart_set_rx_interrupt_level(&USARTD0, USART_INT_LVL_LO);
	 
	 	PORTD.OUTSET = PIN7_bm; //Let's TX
	 	PORTD.DIRSET = PIN7_bm; //TX pin as output

	 	PORTD.OUTCLR = PIN6_bm;
	 	PORTD.DIRCLR = PIN6_bm; //PC6 as RX
	 	
	 	PORTD.DIRCLR = PIN5_bm; //SLAVE INPUT
	 	
		 
	 static usart_rs232_options_t USART_SERIAL_OPTIONS_D1 = {
		 //NO SE PONE VELOCIDAD DE RELOJ YA QUE ES ESCLAVO SINCRONICO
		 .charlength = USART_CHSIZE_8BIT_gc,
		 .paritytype = USART_PMODE_DISABLED_gc,
		 .stopbits = false
	 };
	 usart_init_rs232(&USARTD1,&USART_SERIAL_OPTIONS_D1);
	 usart_set_mode(&USARTD1, USART_CMODE_SYNCHRONOUS_gc);  //MODO SINCRONICO
	 usart_set_rx_interrupt_level(&USARTD1, USART_INT_LVL_LO);
	 
	 PORTE.DIR=0;
	 PORTE.PIN0CTRL|=PORT_OPC_PULLUP_gc|PORT_ISC_FALLING_gc;
	 PORTE.INT0MASK = PIN0_bm;
	 PORTE.INTCTRL = PORT_INT0LVL_LO_gc;
	 
	 PORTA.DIR=255;
	 PORTA.OUT=0;
	 
	 PORTB.DIR=0;
	 PORTB.PIN0CTRL=PORT_OPC_PULLUP_gc;
	 PORTB.PIN1CTRL=PORT_OPC_PULLUP_gc;
	 PORTB.PIN2CTRL=PORT_OPC_PULLUP_gc;
	 PORTB.PIN3CTRL=PORT_OPC_PULLUP_gc;
	 
	pmic_init();
	sei();
	 _delay_ms(1000);
	 
	 while (1)
	 {	 
			 
// 			 if(received_byte=='a')
// 			 {
// 				 PORTA.OUTTGL=PIN0_bm;
// 				 received_byte=0;
// 			 }

			PORTA.OUT=received_byte;


	 }


}

ISR (PORTE_INT0_vect)
{
	//PORTA.OUTTGL=PIN1_bm;
	usart_putchar(&USARTD0,PORTB.IN);
	while (!usart_tx_is_complete(&USARTD0)) {
	}
 

}
ISR(USARTD0_RXC_vect)
{

}
ISR(USARTD1_RXC_vect)
{
   received_byte = usart_getchar(&USARTD1);  //recibe pero no en forma de interrupcion
}