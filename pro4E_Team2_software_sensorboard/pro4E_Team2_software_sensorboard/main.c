/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 17.03.2016 15:21:02
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void init_adc(void); 
int read_adc(void);

void init(void)
{
	PORTB = 0b00000000;
	DDRB = 0b00111111;
	PORTC = 0b00000000;
	DDRC = 0b00000000;
}
	
int main(void)
{
	init_adc();
	init();
	
	int value;
	//int value_mv;
	
	while(1)
	{
		value = read_adc();
		//value_mv = (double)value;
		PORTB = value;
		//printf("\nWert: %i \rButton: %i", value, value_mv);
		_delay_ms(100);
	}
	
	return 0;
}

void init_adc(void)
{
	ADMUX = 01000101; //AVCC with external capacitor at AREF pin, Pin ADC0
	ADCSRA |= (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //Binary: 0b10000111, ADC is enabled, division factor is 128
}

int read_adc(void)
{
	ADCSRA = ADCSRA | (1<<6);
	while(ADCSRA & (1<<6))
	{

	}
	return ADC;
}