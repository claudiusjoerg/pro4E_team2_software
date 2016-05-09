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

void displayAktualisieren();
void initIO();

void initIO(void)
{
	DDRB = 0b00000000;
	PORTB = 0b10000100;
	
	DDRC = 0b00000000;
	PORTC = 0b00010000;
	
	DDRD = 0b00000000;
	PORTD = 0b00111100;
}
	
int main(void)
{
	// Ladezeit für das Aufstarten der Spannungsversorguung
	_delay_ms(500);

	// Einstellungen für Bildschirm
	static FILE fd_lcd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_lcd;
	
	// Peripheriegeräte laden
	//initIO();
	init_lcd();
	//initSPI();
	
	_delay_ms(100);
	
	while(1)
	{
		displayAktualisieren();
		_delay_ms(1000);
	}
	
	return 0;
}

// Diese Methode wird aufgerufen, wenn das Display aktualisiert werden soll
void displayAktualisieren()
{
	// Zeile für Spannung
	lcd_cursor_addr(LINE1);
	printf("For Runners");
	// Zeile für Strom
	lcd_cursor_addr(LINE2);
	printf("Bun Di");
	// Zeile für Prozent
	lcd_cursor_addr(LINE3);
	printf("Bun Di");
	// Zeile für Modus
	lcd_cursor_addr(LINE4);
	printf("Bun Di");
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
