/*
 * pro4E_Team2_software_reportboard.c
 *
 * Created: 19.04.2016 13:12:00
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd_UNO.h"
#include "SPI.h"
#include "incrEnc.h"

void displayAktualisieren();
void initIO();
void initISR();

volatile char enc_delta;
volatile int button;

void initIO(void)
{
	//DDRB = 0b00000001;
	//PORTB = 0b10000100;
	
	//DDRC = 0b00000000;
	//PORTC = 0b00010000;
	
	//DDRD = 0b00000000;
	//PORTD = 0b00111100;
}
	
int main(void)
{
	// Ladezeit für das Aufstarten der Spannungsversorguung
	_delay_ms(500);

	// Einstellungen für Bildschirm
	static FILE fd_lcd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_lcd;
	
	// Peripheriegeräte laden
	initIO();
	init_lcd();
	init_encoder();
	initISR();
		
	_delay_ms(100);

	while(1)
	{
		if (button == 1)
		{
			PORTD |= (1<<0);
		}else{
			PORTD |= (0<<0);
		}
		
		enc_delta;
		
		displayAktualisieren();
		
		_delay_ms(1000);
	}
	
	return 0;
}

void displayAktualisieren()
{
	// Zeile für Spannung
	lcd_cursor_addr(LINE1);
	printf("Zeile 1");
	// Zeile für Strom
	lcd_cursor_addr(LINE2);
	printf("Zeile 2");
	// Zeile für Prozent
	lcd_cursor_addr(LINE3);
	printf("Zeile 3");
	// Zeile für Modus
	lcd_cursor_addr(LINE4);
	printf("Zeile 4\n");
}

void initISR ()
{
	TCCR0B = 0b010; // Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);	//enable timer interrupt
	sei();	
}

ISR (TIMER0_OVF_vect)
{
	button = check_button();
	enc_delta = encodeFunc();
}