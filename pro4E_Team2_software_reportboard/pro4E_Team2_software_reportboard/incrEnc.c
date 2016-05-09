/*
 * pro4E_Team2_software_reportboard.c
 *
 * Created: 09.05.2016 13:49
 * Author : Sarah
 */ 

void incrEnc()
{
	
	
}
#define LED1 = 0;
#define LED2 = 1;
#define A = 2;
#define B = 3;

DDRB = 0b00000011;//pins B1-B8 werden auf in- bzw. output gestellt
PORTB = 0b00000000;//startzustand fuer signal der pins einstellen

while(PORTB2|==)
{
	
}






	TCCR0A = 1<<CS01;			//divide by 8 * 256
	TIMSK0 = 1<<TOIE0;			//enable timer interrupt

	DDRB = 0xFF;
	sei();
	for(;;)				// main loop
	PORTB = enc_delta;
