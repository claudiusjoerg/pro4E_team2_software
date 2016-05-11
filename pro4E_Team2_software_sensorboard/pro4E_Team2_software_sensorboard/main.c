/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 17.03.2016 15:21:02
 * Author : Claudius
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

//My .h-files
#include "ADC.h"
#include "SPI.h"
#include "Tranceiver.h"
#include "uart.h"

#define LED1 6
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 7
#define LED6 5
#define ADCwert	PINB4
#define ChipSelect PORTD
#define OFF 1
#define ON 0
#define SelectADC PORTD //1...7 
#define SelectTranceiver PORTD //1...7

void init(void)
{
	//Output (low): DDxn 1, Portxn 0
	//LED1 = PIND6;LED2 = PINB1;LED3 = PINB2;LED4 = PINB4;LED5 = PIND7;LED6 = PIND5;
	PORTB = 0b00000000;
	DDRB |= (0<<7)|(0<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);
	PORTC = 0b00000000;
	DDRC |= (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0);
	PORTD = 0b00000100;
	DDRD |= (1<<7)|(1<<6)|(0<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);
	
	//Transceiver
	//UARTSPI = 0; //Select SPI
}

	
int main(void)
{
	//init_adc();
	//SPI_MasterInit();
	init();	
	initSPI();

	while(1)
	{
		
		ADC_receive();
		_delay_ms(20);

	}
	
	return 0;
}



