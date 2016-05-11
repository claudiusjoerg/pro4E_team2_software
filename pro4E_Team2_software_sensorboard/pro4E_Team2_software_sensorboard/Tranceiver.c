#include "Tranceiver.h"

#include "uart.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


//#include "uart.h"
void Tranc_init(){
	PORTC4=0b00000001;//Choose UART
	
}

void