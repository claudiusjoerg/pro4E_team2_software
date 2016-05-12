/*
 * pro4E_Team2_software_reportboard.c
 *
 * Created: 09.05.2016 13:49
 * Author : Sarah
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "incrEnc.h"

#define BUTTONMASK 0b00010000

#define PHASE_A	(EncPins & (1<<EncPIN_A))	// PINC.0
#define PHASE_B (EncPins & (1<<EncPIN_B))	// PINC.1

static int8_t last;
volatile int enc_delta;
volatile int button;


void init_encoder()
{
	EncDDR |= (1<<EncPIN_LED_BT)|(1<<EncPIN_LED3)|(1<<EncPIN_LED2)|(1<<EncPIN_LED1);   //intput 0, output 1
	EncPort = (1<<EncPIN_A)|(1<<EncPIN_B)|(1<<EncPIN_BT); //enable pullups
}

void check_button(void)//entpreller
{
	static char old_button;
	//static int autorepeat;
	char current_button = ~EncPins; //liest invertierte PINS ein, weil Pull-Up
	button |= ~old_button & current_button & (1<<EncPIN_BT);//falls zustand gewechselt: button == 1 	
}

void erz_enc_delta(){
		int8_t new, diff;
		
		new = 0;
		if( PHASE_A )
		new = 3;
		if( PHASE_B )
		new ^= 1;                   // convert gray to binary
		diff = last - new;                // difference last - new
		if( diff & 1 ){               // bit 0 = value (1)
			last = new;                 // store new as next last
			enc_delta += (diff & 2) - 1;        // bit 1 = direction (+/-)
		}
}



/*int8_t encode_read2( void )         // read two step encoders
{
	int8_t val;
	
	cli();
	val = enc_delta;
	enc_delta = val & 1;
	sei();
	return val >> 1;
}*/

void controlLED()			//DREHGEBER
{
	/*Knopffunktion*/
			
	if(button==1)      //button gedrückt
	{
		PORTD |= (1<<EncPIN_BT);  //button-LED leuchtet nun
	}
			
	/*Drehfunktion*/
	switch(enc_delta%3)
	{  //enc.Var. zw. -127...128 zeigt position an
		case 1:
		PORTD |= (1<<EncPIN_LED1);
		break;
		case -1:
		PORTD |= (1<<EncPIN_LED3);
		break;
		case 2:
		PORTD |= (1<<EncPIN_LED2);
		break;
		case -2:
		PORTD |= (1<<EncPIN_LED2);
		break;
		case 3:
		PORTD |= (1<<EncPIN_LED3);
		break;
		case -3:
		PORTD |=  (1<<EncPIN_LED1);
		break;
				
		default:
		/*if(enc_delta%3==0)
		{
			if(enc_delta>0)  // im uhrzeigersinn
			{
				PORTD |= (1<<EncPIN_LED3);     //alle mit leuchtendem LED3, go to case 3
			}
			else             // im gegenuhrzeigersinn
			{
				PORTD |= (1<<EncPIN_LED1);    //alle mit leuchtendem LED1, go to case-3
			}
		}
		if((enc_delta+1)%3==0)
		{
			PORTD |= (1<<EncPIN_LED2);      // auf beide seite leuchtet LED2, go to case 2
		}
		if((enc_delta-1)%3==0)
		{
			if(enc_delta>0)    //im uhrzeigersinn
			{
				PORTD |= (1<<EncPIN_LED1);   //alle mit leuchtendem LED1, go to case 1
			}
			else               // im gegenuhrzeigersinn
			{
				PORTD |= (1<<EncPIN_LED3); // go to case -1
			}
		}*/
		break;
	}
}

void init_ISR()
{
	//Initialisierung time interrupt
	TCCR0B = 0b101; // Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);	//enable timer interrupt
	sei();
}

ISR( TIMER0_OVF_vect )             // 1ms for manual movement
{
	erz_enc_delta();
	check_button();					//schaut ob button gedrückt
	//timercounter++;
}

