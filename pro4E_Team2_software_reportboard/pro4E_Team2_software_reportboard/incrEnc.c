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

// Pins definieren
#define BUTTONMASK 0b00010000

#define EncPort_A PORTD
#define EncPort_B PORTD
#define EncPort_BT PORTD

#define EncPIN_A 6
#define EncPIN_B 5
#define EncPIN_BT 4
#define EncPIN_LED_BT 0
#define EncPIN_LED3 1
#define EncPIN_LED2 2
#define EncPIN_LED1 3

#define EncDDR DDRD

#define BUTTON (1<<4)
#define MODE (1<<4)
#define CNT_MAX 10
#define CNT_MIN 0
#define AUTOREPEAT_SET 50

#define PHASE_A	(EncPort_A & 1<<EncPIN_A)	// PINC.0
#define PHASE_B (EncPort_B & 1<<EncPIN_B)	// PINC.1

char enc_delta;		// -128 ... 127
volatile int button = 0;

void init_encoder()
{
	EncDDR |= (0<<EncPIN_A)|(0<<EncPIN_B)|(0<<EncPIN_BT)|(1<<EncPIN_LED_BT)|(1<<EncPIN_LED3)|(1<<EncPIN_LED2)|(1<<EncPIN_LED1);   //intput 0, output 1
}

static void check_button(void)//entpreller
{
	static char old_button;
	//static int autorepeat;
	char current_button = ~PIND; //liest invertierte PINS ein, weil Pull-Up
	button |= ~old_button & current_button & BUTTONMASK;//falls zustand gewechselt: button == 1 	
}

void encodeFunc()
{
	static char enc_last = 0x01;
	char i = 0;

	if( PHASE_A )
	i = 1;

	if( PHASE_B )
	i ^= 3;				// convert gray to binary

	i -= enc_last;			// difference new - last

	if( i & 1 ){				// bit 0 = value (1)
		enc_last += i;			// store new as next last

		enc_delta += (i & 2) - 1;		// bit 1 = direction (+/-)
	}
}
	
void controlLED()
{
	/*Knopffunktion*/
	if(button==1)      //button gedrückt
	{
		1<<EncPIN_BT;  //button-LED leuchtet nun
	}
	
	/*Drehfunktion*/
	switch(enc_delta){  //enc.Var. zw. -127...128 zeigt position an
	case 1:
		1<<EncPIN_LED1;
		break;
	case -1:
		1<<EncPIN_LED3;
		break;
	case 2:
		1<<EncPIN_LED2;
		break;
	case -2:
		1<<EncPIN_LED2;
		break;
	case 3:
		1<<EncPIN_LED3;
		break;
	case -3:
		1<<EncPIN_LED1;
		break;
	
	default:
		if(enc_delta%3==0)
		{
			if(enc_delta>0)  // im uhrzeigersinn
			{
			1<<EncPIN_LED3;     //alle mit leuchtendem LED3, go to case 3
			}
			else             // im gegenuhrzeigersinn
			{
			1<<EncPIN_LED1;    //alle mit leuchtendem LED1, go to case-3
			}
		}
		if((enc_delta+1)%3==0)
		{
			1<<EncPIN_LED2;      // auf beide seite leuchtet LED2, go to case 2
		}
		if((enc_delta-1)%3==0)
		{
			if(enc_delta>0)    //im uhrzeigersinn
			{
				1<<EncPIN_LED1;   //alle mit leuchtendem LED1, go to case 1
			}
			else               // im gegenuhrzeigersinn
			{
				1<<EncPIN_LED3; // go to case -1
			}
		}
		break;
	}
}


void initISR ()
{
	TCCR0B = 0b010; // Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);	//enable timer interrupt
	sei();
}

ISR (TIMER0_OVF_vect)
{
	button;
	enc_delta;
}