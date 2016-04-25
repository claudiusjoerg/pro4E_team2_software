/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 17.03.2016 15:21:02
 * Author : Claudius
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED1 6
#define LED2 1
#define LED3 2
#define LED4 4 //Wurde angepasst, überprüfen!!
#define LED5 7
#define LED6 5
#define ADCwert	PINB3
#define ChipSelect PORTD
#define OFF 1
#define ON 0

void init_adc(void); 
void SPI_MasterInit(void);
int read_adc(void);

void init(void)
{
	//Output (low): DDxn 1, Portxn 0
	//LED1 = PIND6;LED2 = PINB1;LED3 = PINB2;LED4 = PINB4;LED5 = PIND7;LED6 = PIND5;
	PORTB = 0b00000000;
	DDRB |= (0<<7)|(0<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);
	PORTC = 0b00000000;
	DDRC |= (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0);
	PORTD = 0b00000000;
	DDRD |= (1<<7)|(1<<6)|(0<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);
}
//void UART_init()
//{
//UCSR0A = 0; //(0<<U2Xn) - Ubrr = 16 bei 16MHz
//}
	
int main(void)
{
	//init_adc();
	//SPI_MasterInit();
	init();
	
	int value;
	
	while(1)
	{
		ChipSelect = ON;
		value = ADCwert;
		PORTD |= (value & 0x1<<LED1);
		PORTB |= (value & 0x2<<LED2);
		PORTB |= (value & 0x4<<LED3);
		PORTB |= (value & 0x8<<LED4);
		PORTD |= (value & 0x10<<LED5);
		PORTD |= (value & 0x20<<LED6);
		ChipSelect = OFF;
		_delay_ms(50);
	}
	
	return 0;
}
/*
// SPI Communication
void SPI_MasterInit(void)
{
	// Set MOSI and SCK output, all others input
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)))
	;
}*/

/*void init_adc(void)
{
	ADMUX = 01000101; //AVCC with external capacitor at AREF pin, Pin ADC0
	ADCSRA |= (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //Binary: 0b10000111, ADC is enabled, division factor is 128
}

int read_adc(void)
{
	ADCSRA = ADCSRA | (1<<6);
	while(ADCSRA & (1<<6))
	{

	}
	return ADC;
}*/