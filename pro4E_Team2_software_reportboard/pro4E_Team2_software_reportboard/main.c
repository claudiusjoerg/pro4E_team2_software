/*
 * pro4E_Team2_software_reportboard.c
 *
 * Created: 19.04.2016 13:12:00
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void init(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
}
	
int main(void)
{
	init();
	
	while(1)
	{
		//printf("\nWert: %i \rButton: %i", value, value_mv);
		_delay_ms(100);
	}
	
	return 0;
}