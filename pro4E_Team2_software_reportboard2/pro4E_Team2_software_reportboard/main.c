

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
#include "incrEnc.h"
#include "board.h"
#include "menutree.h"
#include "menutree_demo.h"
//#include "SPI.h"


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
	init_lcd();
	init_encoder();
	init_ISR();
	
	// Lädt das Hauptmenu
	//while (!read_buttons());
	LoadMenu(MainMenu);
		
	_delay_ms(100);
	
	//7int d = 0;

	while(1)
	{
<<<<<<< HEAD
		//enc_delta = encode_read2();
		//controlLED();
		
		lcd_cursor_addr(LINE1);
		printf("enc_delta = %d", enc_delta);
		lcd_cursor_addr(LINE2);
		printf("button is %s\n", (button&BUTTON)? "set":"reset"); // falls button gedrückt schreibe set sonst reset.
		
		EncPort = EncPort & (~BUTTON|button);
		EncPort = (EncPort & ~((0b111)<<EncPIN_LED1)) | (enc_delta & 0b111)<<EncPIN_LED1;
	
		_delay_ms(200);
=======
		/*
		lcd_cursor_addr(LINE1);
		printf("Timer:%i",d++);
		lcd_cursor_addr(LINE2);
		printf("Counter:%i",timercounter);
		*/
		//controlLED();
		printf("enc_delta=%d\rbutton is %s", enc_delta, (button & BUTTON)?"set":"reset");
		
		EncPort = EncPort & (~BUTTON | button);		
		EncPort = (EncPort & ~((0b111)<<EncPIN_LED1)) | (enc_delta & 0b111)<<EncPIN_LED1;
		_delay_ms(200);
		
>>>>>>> 381a3683190a04d386228775510bde2c96182d4c
	}
	
	return 0;
}