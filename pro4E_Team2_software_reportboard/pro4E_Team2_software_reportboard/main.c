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

void init(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
}
	
int main(void)
{
	// Ladezeit für das Aufstarten der Spannungsversorguung
	_delay_ms(500);

	// Einstellungen für Bildschirm
	static FILE fd_lcd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_lcd;
	
	// Peripheriegeräte laden
	init_lcd();
	init();
	
	_delay_ms(100);
	
	while(1)
	{
		//printf("\nWert: %i \rButton: %i", value, value_mv);
		_delay_ms(100);
	}
	
	return 0;
}

// Diese Methode wird aufgerufen, wenn das Display aktualisiert werden soll
void displayAktualisieren(int spannung, int strom, int prozent, int modus)
{
	// Zeile für Spannung
	lcd_cursor_addr(LINE1);
	//spannung/=10;
	//if (spannung>999)
	//{
		//printf("Spannung: %d.%02dV",spannung/100,spannung%100);
	//}
	//else if (spannung<1000)
	//{
		//printf("Spannung:  %d.%02dV",spannung/100,spannung%100);
	//}
	// Zeile für Strom
	lcd_cursor_addr(LINE2);
	//printf("Strom:     %d.%02dA", strom/100,strom%100);
	// Zeile für Prozent
	lcd_cursor_addr(LINE3);
	//if (prozent>99)
	//{
		//printf("Bestrahlung:%i%%",prozent);
	//}
	//else if (prozent<100)
	//{
		//printf("Bestrahlung: %i%%",prozent);
	//}
	// Zeile für Modus
	lcd_cursor_addr(LINE4);
	//if (modus==MODUSSAUBER)
	//{
		//printf("Modus:    Sauber");
	//}
	//else if (modus==MODUSVERSCHMUTZT)
	//{
		//printf("Modus: Schmutzig");
	//}
}