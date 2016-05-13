#include <avr/io.h>
#include <util/delay.h>


#include "ADC.h"

void init_adc(void)
{
	ADMUX = 0b01000101; //AVCC with external capacitor at AREF pin, Pin ADC0
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