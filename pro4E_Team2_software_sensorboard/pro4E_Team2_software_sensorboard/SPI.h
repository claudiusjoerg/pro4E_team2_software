#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Tranceiver.h"
#include "uart.h"

void initSPI();

char ADC_receive();