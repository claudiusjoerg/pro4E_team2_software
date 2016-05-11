#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Tranceiver.h"
#include "uart.h"

#define REGDATA		3
#define RXTX		6
#define UART		

void Tranc_init(){
	PORTC4 = 0b00000001;			// Choose UART
	
}