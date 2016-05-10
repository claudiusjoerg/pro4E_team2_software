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

#define BUTTON (1<<2)
#define MODE (1<<4)
#define CNT_MAX 10
#define CNT_MIN 0
#define AUTOREPEAT_SET 50

#define PHASE_A	(EncPort_A & 1<<EncPIN_A)	// PINC.0
#define PHASE_B (EncPort_B & 1<<EncPIN_B)	// PINC.1

volatile char enc_delta;		// -128 ... 127
volatile int button = 0;

void init_encoder()
{
	EncDDR |= (0<<EncPIN_A)|(0<<EncPIN_B)|(0<<EncPIN_BT)|(1<<EncPIN_LED_BT)|(1<<EncPIN_LED3)|(1<<EncPIN_LED2)|(1<<EncPIN_LED1);   //intput 0, output 1
}

static int check_button(void)
{
	static char old_button;
	//static int autorepeat;
	char current_button = ~PIND; //liest invertierte PINS ein, weil Pull-Up
	button |= ~old_button & current_button & BUTTONMASK;
	
	// Button des Drehgebers
	if (button == BUTTON)
	{
		//autorepeat = AUTOREPEAT_SET; //setzt Verzögerung
		button = 1;
	}else{
		button = 0;
	}
}

char encodeFunc()
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
	
void controlLED(value_distance)
{
	/*if(enc_delta>0){  //sind im uhrzeigersinn
		int i=EncPIN_LED1;
		for(int j=0; j<=value_distance; j++)*/

	switch(value_distance){
	case 1:
		if(enc_delta>0){
			1<<EncPIN_LED1;
		}
		else
		{
			1<<EncPIN_LED3;
		}
		break;
		
	case 2:
		1<<EncPIN_LED2;
		break;
		
	case 3:
		if(enc_delta>0){
			1<<EncPIN_LED3;
		}
		else
		{
			1<<EncPIN_LED1;
		}
		break;
	
	default:
		if(value_distance%3==0)
		{
			goto case 3;
		}
		if((value_distance+1)%3==0)
		{
			goto case 2;
		}
		if((value_distance-1)%3==0)
		{
			goto case 1;
		}
		break;
	}
}
}