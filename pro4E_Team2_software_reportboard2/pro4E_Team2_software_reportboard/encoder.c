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
#include "encoder.h"

#define PHASE_A	(Encpins & (1<<EncPIN_A))	// PINC.0
#define PHASE_B (Encpins & (1<<EncPIN_B))	// PINC.1

static int last;
volatile int enc_delta;
volatile int button;

void init_encoder()
{
	EncDDR |= (1<<EncPIN_LED_BT)|(1<<EncPIN_LED3)|(1<<EncPIN_LED2)|(1<<EncPIN_LED1);   //intput 0, output 1
	EncPort = (1<<EncPIN_A)|(1<<EncPIN_B); //enable pull ups	|(1<<EncPIN_LED_BT)
}

static void check_button(void)										//entpreller
{
	static char old_button;
	char current_button = ~Encpins;							// weil Pull-Up, pins werden invertiert eingelesen
	button |= ~old_button & current_button & PUSHBUTTON;		// button (byte) wird eins sein, wenn alter button invertiert eins ist, button eins und BUTTON(mask) eins (filtert pins der angeschlossenen buttons)	
	old_button = current_button;	// wichtige Zeile, damit button einmal als gedrückt erkannt wird.
}

/*Diese Methode is von MIkrocontroller.net*/
void erz_enc_delta(){
		int new, diff;
		
		new = 0;
		
		if(PHASE_A){
			new = 3;
		}
		if(PHASE_B){
			new ^= 1;						// convert gray to binary
		}
		
		diff = last - new;					// difference last - new
		if( diff & 1 ){						// lsb = value (1)
			last = new;						// store new as next last
			enc_delta += (diff & 2) - 1;	// 2.lsb = direction (+/-), minus1 für 2er-kompl
		}
}

int encode_read_encdelta( void )         // read four step encoders
{
	int val;
	
	cli();
	val = enc_delta;
	enc_delta = 0;
	sei();
	return val;
}

int encode_read_button( void )         // read four step encoders
{
	int val;
	
	cli();
	val = button;
	button = 0;
	sei();
	return val;
}

void init_ISR()
{
	//Initialisierung timer interrupt
	TCNT0 = 0;
	TCCR0B = 0b101;					// Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);			//enable timer interrupt
}

ISR( TIMER0_OVF_vect )				// 1ms for manual movement
{
	erz_enc_delta();
	check_button();					//schaut ob button gedrückt
}