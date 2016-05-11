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
#include "board.h"
#include "menutree.h"

void displayAktualisieren();
void initIO();


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

	// Einstellung für Bildschirm
	static FILE fd_lcd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_lcd;
	
	// Peripheriegeräte und Funktionen laden
	initIO();
	init_lcd();
	init_encoder();
	
	while (!read_buttons());
	LoadMenu(MainMenu);
		
	_delay_ms(100);

	while(1)
	{
		//displayAktualisieren();
		
		int buttons;
		buttons = check_button();
		if (buttons) {
			ProcessMenu(buttons);
		}
		
		_delay_ms(1000);
	}
	
	return 0;
}
/*
void displayAktualisieren()
{

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
*/

