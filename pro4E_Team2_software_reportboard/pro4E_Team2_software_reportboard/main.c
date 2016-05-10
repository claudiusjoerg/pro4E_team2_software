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

#define PHASE_A	(PINC & 1<<PINC0)	// PINC.0
#define PHASE_B (PINC & 1<<PINC1)	// PINC.1

void displayAktualisieren();
void initIO();

volatile char	enc_delta;		// -128 ... 127

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
	//initSPI();
	
	TCCR0A = 1<<CS01;			//divide by 8 * 256
	TIMSK0 = 1<<TOIE0;			//enable timer interrupt

	DDRB = 0xFF;
	sei();
	for(;;)				// main loop
	PORTB = enc_delta;
	
	
	_delay_ms(100);

	while(1)
	{
		displayAktualisieren();
		//printf("NEIN NEIN %d\n", i++);
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
/*
// Startet die SPI-Schnittstelle
void initSPI()
{
	SPI_DDR |= (1<<P_MOSI)|(1<<P_SCLK); // Pins als Output für SPI definieren
	SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0); // Einstellungen für SPI
	DDRB|=0b00001100; // B2 (CS) und B3 (LOADDACS) als Output setzen
	PORTB&=~(LOADDACS); // LOADDACS auf LOW setzen
	PORTB|=CS; // CS auf HIGH setzen
}

// Übermittelt Daten über SPI
void transmitSPI(int cData)
{
	PORTB|=LOADDACS; // LOADDACS auf HIGH setzen
	PORTB&=~(CS); // CS auf LOW setzen
	_delay_us(1); // Delay min. 15ns
	// Start transmission 
	SPDR = cData;
	//Wait for transmission complete
	while(!(SPSR & (1<<SPIF)))
	;
	_delay_us(1); // Delay min. 15ns
	PORTB|=CS; // CS auf HIGH setzen
	PORTB&=~(LOADDACS); // LOADDACS auf LOW setzen
}*/

SIGNAL (SIG_OVERFLOW0)
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