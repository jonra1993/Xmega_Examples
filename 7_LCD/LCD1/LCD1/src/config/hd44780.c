//-------------------------------------------------------------------------------------------------
// Wyúwietlacz alfanumeryczny ze sterownikiem HD44780
// Sterowanie w trybie 4-bitowym bez odczytu flagi zajÍtoúci
// z dowolnym przypisaniem sygna≥Ûw sterujπcych
// Plik : HD44780.c	
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor : Rados≥aw KwiecieÒ
// èrÛd≥o : http://radzio.dxp.pl/hd44780/
// Data : 24.03.2007
//
// Dostosowanie do procesorÛw XMEGA
// Dominik Leon BieczyÒski
// Leon Instruments
// http://leon-instruments.blogspot.com
//-------------------------------------------------------------------------------------------------
#include <stdlib.h>
#include "hd44780.h"
#include <avr/pgmspace.h>

void CustChar(unsigned char c, char *data) {
	LcdCommand(0x40+((c&0x07)<<3)); //Set CG-RAM address
	for (char i=0; i<8; i++) {
    LcdData(*data++);
	}
}
//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the
// specified position.
//
void SendString(char *pt, int line, int position)
{
	if (line == 1)
	LcdCommand(0x80 + position);
	else
	LcdCommand(0xc0 + position);
	while (*pt)
	LcdData(*pt++);
}
//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the
// specified position.
//
void SendInt(int number, int line, int position)
{
	char temp[15];
	
	itoa(number, temp, 10);
	SendString(temp, line, position);
}

//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the
// specified position.
//
void SendFloat(float value, int line, int position)
{
	char temp[15];

	dtostrf(value, 3, 2, temp);
	SendString(temp, line, position);
}
// Convert the number to the equeivelent ascii string.
//
void sprintl(long number, char *pt)
{
	int i, a, flag;
	long divisor = 1000000000L;
	
	if (number < 0L)
	*pt++ = '-';
	
	if (number == 0L)
	{
		*pt++ = '0';
	}
	else
	{
		flag = 0;
		for (i=1; i<11; i++)
		{
			a = (int)(number / divisor);
			if (a > 0)
			{
				flag = 1;
				number = number - (long)a * divisor;
			}
			if (flag)
			{
				*pt++ = '0' + (char)a;
			}
			divisor /= 10L;
		}
	}
	*pt = '\0';
}

//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the
// specified position.
//
void SendLong(long number, int line, int position)
{
	char temp[15];

	sprintl(number, temp);
	SendString(temp, line, position);
}


static void _lcd_OutNibble(unsigned char nibbleToWrite) {
	if(nibbleToWrite & 0b00000001)
		LCD_PORT.OUTSET = LCD_D4_bm;
	else
		LCD_PORT.OUTCLR = LCD_D4_bm;

	if(nibbleToWrite & 0b00000010)
		LCD_PORT.OUTSET = LCD_D5_bm;
	else
		LCD_PORT.OUTCLR = LCD_D5_bm;

	if(nibbleToWrite & 0b00000100)
		LCD_PORT.OUTSET = LCD_D6_bm;
	else
		LCD_PORT.OUTCLR = LCD_D6_bm;

	if(nibbleToWrite & 0b00001000)
		LCD_PORT.OUTSET = LCD_D7_bm;
	else
		LCD_PORT.OUTCLR = LCD_D7_bm;
}

static void _lcd_Write(unsigned char dataToWrite) {
	LCD_PORT.OUTSET = LCD_E_bm;
	_lcd_OutNibble(dataToWrite >> 4);
	LCD_PORT.OUTCLR = LCD_E_bm;
 	asm volatile("nop");
	LCD_PORT.OUTSET = LCD_E_bm;
	_lcd_OutNibble(dataToWrite);
	LCD_PORT.OUTCLR = LCD_E_bm;
	_delay_us(50);
}

void LcdCommand(unsigned char commandToWrite) {
	LCD_PORT.OUTCLR = LCD_RS_bm;
	_lcd_Write(commandToWrite);
}

void LcdData(unsigned char dataToWrite) {
	LCD_PORT.OUTSET = LCD_RS_bm;
	_lcd_Write(dataToWrite);
}

void LcdWrite(char * text) {
	while(*text) LcdData(*text++);
}

void LcdWriteProgmem(const char * data) {
	char bufor;
	while ((bufor = (char)pgm_read_byte(data++))) LcdData(bufor);
}

void LcdGoto(unsigned char x, unsigned char y) {
	LcdCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}

void LcdClear(void) {
	LcdCommand(HD44780_CLEAR);
	_delay_ms(2);
}

void LcdInit(void) {
	LCD_PORT.DIRSET	=	LCD_D4_bm|
						LCD_D5_bm|
						LCD_D6_bm|
						LCD_D7_bm|
						LCD_RS_bm|
						LCD_E_bm;
	_delay_ms(5); // oczekiwanie na ustalibizowanie siÍ napiecia zasilajacego
	LCD_PORT.OUTCLR = LCD_RS_bm | LCD_E_bm;

	for(uint8_t i = 0; i < 3; i++) { // trzykrotne powtÛrzenie bloku instrukcji
		LCD_PORT.OUTSET = LCD_E_bm;
		_lcd_OutNibble(0x03); // tryb 8-bitowy
		LCD_PORT.OUTCLR = LCD_E_bm;
		_delay_ms(5); // czekaj 5ms
	}

	LCD_PORT.OUTSET = LCD_E_bm;
	_lcd_OutNibble(0x02); // tryb 4-bitowy
	LCD_PORT.OUTCLR = LCD_E_bm;

	_delay_ms(1); // czekaj 1ms 
	LcdCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
	LcdCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wy≥πczenie wyswietlacza
	LcdCommand(HD44780_CLEAR); // czyszczenie zawartosÊi pamieci DDRAM
	_delay_ms(2);
	LcdCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
	LcdCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // w≥πcz lcd, bez kursora i mrugania
}

void LcdDec(uint32_t liczba) {
	if(liczba==0) {
		LcdData('0');
		return;
	}
	
	uint8_t cyfra[10] ; 
	int8_t i=0;
	
	while(liczba) {
		cyfra[i] = (uint8_t)(liczba%10);
		liczba = liczba / 10;
		++i;
	}
	--i;

	for(;i>=0;--i) {
		LcdData(cyfra[i]+48);
	}  

}

//-------------------------------------------------------------------------------------------------
//
// Koniec pliku HD44780.c
//
//-------------------------------------------------------------------------------------------------
