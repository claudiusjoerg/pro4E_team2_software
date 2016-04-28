/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 17.03.2016 15:21:02
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

//
#include "ADC.h"
#include "SPI.h"

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

void init_adc(void); 
//void SPI_MasterInit(void);
//void SPI_MasterTransmit();
//int read_adc(void);

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
}
//void UART_init()
//{
//UCSR0A = 0; //(0<<U2Xn) - Ubrr = 16 bei 16MHz
//}
	
int main(void)
{
	//init_adc();
	SPI_MasterInit();
	init();
	
	int value;
	char startConv;
	
	while(1)
	{
		startConv = 0b00000001; //Last Bit is the Start Bit
		SPI_MasterTransmit(startConv);
		startConv = 0b10100000; //SGL/Diff - ODD/SIGN - MSBF: Single Ended Mode, CH0 selected, MSB first format
		SPI_MasterTransmit(startConv);
		PORTB = (1<<3); //signal the end of packet
		ChipSelect = ON;
		value = ADCwert;
		ChipSelect = OFF;
		PORTD |= (value & 0x1<<LED1);
		PORTB |= (value & 0x2<<LED2);
		PORTD |= (value & 0x4<<LED3);
		PORTD |= (value & 0x8<<LED4);
		PORTD |= (value & 0x10<<LED5);
		PORTD |= (value & 0x20<<LED6);
		
		_delay_ms(50);
	}
	
	return 0;
}



