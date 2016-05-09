#include <avr/io.h>
#include <util/delay.h>


#include "SPI.h"

void SPI_MasterInit(void)
{
	// Set MOSI and SCK output, all others input
	DDRB = (1<<DDB3)|(1<<DDB5);
	// Enable SPI, Master, set clock rate f_ck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
char SPI_MasterTransmit(char cData)
{
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF))) //SPIF Transmission Flag
	;
	return SPDR;
}