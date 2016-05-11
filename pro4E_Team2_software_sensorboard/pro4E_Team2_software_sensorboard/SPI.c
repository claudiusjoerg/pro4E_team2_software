#include <avr/io.h>
#include <util/delay.h>


#include "SPI.h"

void initSPI(){
	DDRB = (1<<PORTB3)|(1<<PORTB5)|(1<<PORTB2);//0b011100;
	SPCR &= ~((1<<CPOL)|(1<<DORD));
	SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<CPOL)|(1<<SPR0));
	//SPCR &= ~((1<<SPR1)|(1<<SPR0));				//f_transmit = fosc/64 --> 16MHz/64
	//SPSR &= ~(1<<SPI2X);// Doppelte Geschwindigkeit
	//SPSR |= (1<<SPI2X);
}


char ADC_receive(){
	//transmit
	char Dout= 0b1101;				//Startbit + Config die über SPI gesendet werden müssen
	
	// Start transmission (MOSI)
	SPDR = Dout;
	
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}