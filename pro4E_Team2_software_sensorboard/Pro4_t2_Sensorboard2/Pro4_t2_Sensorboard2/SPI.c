
#include "SPI.h"


void initSPI(){
	//(MOSI, Clock, SS )= OUTPUT
	DDRB = ((1<<PORTB5)|(1<<PORTB2));//0b011100;
	//MSB first
	SPCR &=~((1<<DORD));
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<SPR0));

	//0: Daten werden bei steigender Taktflanke (=abh. von CPOL) eingelesen, bei fallender ausgegeben
	//0: Takt ist in Ruhe LOW, ein Wechsel auf HIGH zählt als steigende Taktflanke
	SPCR &= ~((1<<CPHA)|(1<<CPOL));	
	//SPCR &= ~((1<<SPR1)|(1<<SPR0));				//f_transmit = fosc/64 --> 16MHz/64
	//SPSR &= ~(1<<SPI2X);// Doppelte Geschwindigkeit
	//SPSR |= (1<<SPI2X);

	PORTB = (1<<PORTB2);//Pull-Up SS
}


uint16_t ADC_receive(){

	uint16_t daten;

	//send Config Data enable MOSI
	send_config(CONFIG);
	daten = receive_data();

	daten = daten<<9;

	send_config(CONFIG);

	daten |= (receive_data()& MASK);

	//SS High
	PORTB |= (1<<PORTB2);
	
	return daten;
}

void send_config(uint8_t config){
//MOSI enable
	DDRB |= (1<<PORTB3);
	//MISO disable
	DDRB &=~(1<<PORTB4);
	//SS low
	PORTB &=~(1<<PORTB2);

	// Start transmission (MOSI)
	SPDR = CONFIG;

	while(!(SPSR & (1<<SPIF)));
}

uint8_t receive_data(){

	uint8_t daten;

	//MOSI disable
	DDRB &= ~(1<<PORTB3);
	//MISO enable
	DDRB |=(1<<PORTB4);
	
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	daten = SPDR;

	return daten;
}