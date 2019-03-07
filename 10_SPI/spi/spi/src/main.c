
#include <asf.h>
#include <util/delay.h>

void	pin_config (void);
void	SPI_init(void);

struct spi_device SPI_DEVICE_1 = {.id = SPI_DEVICE_1_ID};
struct spi_device SPI_DEVICE_2 = {.id = SPI_DEVICE_2_ID};
	
uint8_t IN1[1]={0};
uint8_t IN2[1]={0};
uint8_t OUT1[1]={'a'};
uint8_t OUT2[1]={'p'};
	
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	pin_config();
	SPI_init();	
	irq_initialize_vectors();
	cpu_irq_enable();

	while (1)
	{

		if (IN1[0]=='p')
		{
			PORTA.OUTSET=PIN1_bm;
		}
	}
}
void pin_config (void)
{

	PORTE.DIR=0;
	PORTE.PIN0CTRL|=PORT_OPC_PULLUP_gc|PORT_ISC_FALLING_gc;
	PORTE.PIN1CTRL|=PORT_OPC_PULLUP_gc|PORT_ISC_FALLING_gc;

	PORTA.DIR=0B11;
	PORTA.OUT=0;
	
	PORTE.INT1MASK = PIN1_bm;
	PORTE.INT0MASK = PIN0_bm;
	PORTE.INTCTRL = PORT_INT1LVL_LO_gc|PORT_INT0LVL_LO_gc;

}
ISR (PORTE_INT0_vect)
{
		PORTA.OUTTGL=PIN0_bm;
		spi_select_device(&SPIC,&SPI_DEVICE_1);
		spi_write_packet(&SPIC, OUT1, 1);
		spi_read_packet(&SPIC,IN1,1);
		spi_deselect_device(&SPIC,&SPI_DEVICE_1);	
		
		spi_select_device(&SPID,&SPI_DEVICE_2);
		spi_write_packet(&SPID, OUT2, 1);
		spi_read_packet(&SPID,IN2,1);
		spi_deselect_device(&SPID,&SPI_DEVICE_2);		

}

ISR (PORTE_INT1_vect)
{
	
}
void	SPI_init(void)
{

ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);
ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	
spi_master_init(&SPIC);
spi_master_setup_device(&SPIC, &SPI_DEVICE_1, SPI_MODE_0, 1000000, 0);
spi_enable(&SPIC);	


ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);
ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);

spi_master_init(&SPID);
spi_master_setup_device(&SPID, &SPI_DEVICE_2, SPI_MODE_0, 1000000, 0);
spi_enable(&SPID);

}

