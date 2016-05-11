

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
//#include "SPI.h"
#include "incrEnc.h"
//#include "board.h"
//#include "menutree.h"


<<<<<<< HEAD
=======
<<<<<<< HEAD:pro4E_Team2_software_reportboard/pro4E_Team2_software_reportboard/main.c

volatile int8_t enc_delta;
//volatile char enc_delta;		// -128 ... 127
volatile int button = 0;
static int8_t last;
volatile int8_t menu_Max;
=======

>>>>>>> cd818d65562cc0b44545cfca96a2ef5ebb260b2e:pro4E_Team2_software_reportboard2/pro4E_Team2_software_reportboard/main.c


void initIO(void)
{
	//DDRB = 0b00000001;
	//PORTB = 0b10000100;
	
	//DDRC = 0b00000000;
	//PORTC = 0b00010000;
	
	//DDRD = 0b00000000;
	//PORTD = 0b00111100;
}
>>>>>>> 106cb76223a197fa4a8e5b960e31f035f743cc79
	
int main(void)
{
	// Ladezeit für das Aufstarten der Spannungsversorguung
	_delay_ms(500);

	// Einstellung für Bildschirm
	static FILE fd_lcd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_lcd;
	
	// Peripheriegeräte und Funktionen laden
	init_lcd();
	init_encoder();
	init_ISR();
	
	// Lädt das Hauptmenu
	//while (!read_buttons());
	//LoadMenu(MainMenu);
		
	_delay_ms(100);
	
	int d = 0;

	while(1)
	{
		lcd_cursor_addr(LINE1);
		printf("Timer:%i",d++);
		lcd_cursor_addr(LINE2);
		printf("Counter:%i",timercounter);
		
		enc_delta = encode_read2();
		controlLED();
	
		_delay_ms(1000);
	}
	
	return 0;
}