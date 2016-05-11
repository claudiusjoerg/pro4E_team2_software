#ifndef __TRANCEIVER_H__
#define __TRANCEIVER_H__

#include "uart.h"
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "SPI.h"

#define UART_BAUD_RATE 2400

void init_Tranceiver();

void uebertragung_uart();

#endif
