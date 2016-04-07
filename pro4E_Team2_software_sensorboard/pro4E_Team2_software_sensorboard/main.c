/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 17.03.2016 15:21:02
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>

void init_adc(void);
int read_adc(void);

int main(void)
{
	init_adc();
	
	int value;
	int value_mv;
	int vcc = 5000;
	int PORTA = 0;
	int DDRA = 0;
	
	while(1)
	{
		value = read_adc();
		value_mv = (double)value;
		PORTA = value_mv;
		//printf("\nWert: %i \rButton: %i", value, value_mv);
		_delay_ms(100);
	}
	
	return 0;
}

void init_adc(void)
{
	ADMUX = 01000000; //AVCC = AREF Pin
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