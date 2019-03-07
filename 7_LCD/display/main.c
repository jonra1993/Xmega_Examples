#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"

int main(void) {
	
	// konfiguracja przycisku FLIP
	PORTE.DIRCLR	=	PIN5_bm;				// pin E5 jako wejœcie
	PORTE.PIN5CTRL	=	PORT_OPC_PULLUP_gc;		// podci¹gniêcie do zasilania
	
	// Inicjalizacja wyœwietlacza
	LcdInit();									// inicjalizacja sterownika LCD
	Lcd("   Kurs XMEGA");						// wyœwietlenie napisu
	Lcd2;										// przejœcie do drugiej linii
	Lcd("Leon Instruments");					// wyœwietlenie napisu
	
	// zmienna s³u¿¹ca jako licznik
	uint8_t licznik = 0;
	
	while(1) {
		if(!(PORTE.IN & PIN5_bm)) {				// je¿eli przycisk FLIP jest wciœniêty
			licznik++;							// zwiêksz licznik o 1
			LcdClear();							// wyczyœæ wyœwietlacz
			Lcd("Licznik:");					// wyœwietlenie napisu
			Lcd2;								// przejœcie do drugiej linii
			LcdDec(licznik);					// wyœwietlenie zmiennej liczbowej
			_delay_ms(100);						// czekanie 100ms
		}
	}
}