//
//  DAC.c
//
//
//

//#include "DAC.h"
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


void initSPI(){
	DDRB = 0b0111;
	SPCR &= ~((1<<CPOL)|(1<<DORD));
	SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<CPHA));
	SPCR &= ~((1<<SPR1)|(1<<SPR0));				//f_transmit = fosc/64 --> 16MHz/64
	SPSR &= ~(1<<SPI2X);
	SPSR |= (1<<SPI2X);
}


short ADC_receive(){
	//transmit
	char Din= 0b1101;				//Startbit + Config die über SPI gesendet werden müssen
	
	SPDR = Din;
	while(!(SPSR & (1<<SPIF)));
	return 0;
}


int main(){
	
	initSPI();
	while(1){
		ADC_receive();
		
	}
	
}