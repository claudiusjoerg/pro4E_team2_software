#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "Tranceiver.h"
#include "uart.h"

#define REGDATA		3
#define RXTX		6
#define UART		4

void Tranc_init(){
	PORTC |= (1<<UART);			// Choose UART
	
}