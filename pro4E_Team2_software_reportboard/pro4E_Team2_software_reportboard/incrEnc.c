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
/*#define MODE (1<<4)
#define CNT_MAX 10
#define CNT_MIN 0
#define AUTOREPEAT_SET 50*/

#define PHASE_A	(EncPort_A & 1<<EncPIN_A)	// PINC.0
#define PHASE_B (EncPort_B & 1<<EncPIN_B)	// PINC.1


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

/*void encode_init( void )
{
	int8_t new;
	
	new = 0;
	if( PHASE_A )
	new = 3;
	if( PHASE_B )
	new ^= 1;                   // convert gray to binary
	last = new;                   // power on state
	enc_delta = 0;
	TCCR0 = 1<<WGM01^1<<CS01^1<<CS00;     // CTC, XTAL / 64
	OCR0 = (uint8_t)(XTAL / 64.0 * 1e-3 - 0.5);   // 1ms
	TIMSK |= 1<<OCIE0;
}*/
	



void initISR ()
{
	TCCR0B = 0b010; // Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);	//enable timer interrupt
	sei();
}

/*ISR (TIMER0_OVF_vect)
{
	button;
	enc_delta;
}*/

ISR( TIMER0_COMP_vect )             // 1ms for manual movement
{
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

int8_t encode_read2( void )         // read two step encoders
{
	int8_t val;
	
	cli();
	val = enc_delta;
	enc_delta = val & 1;
	sei();
	return val >> 1;
}