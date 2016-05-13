#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Tranceiver.h"
#include "uart.h"

#define CONFIG 	0b1111	//Startbit + Config die über SPI gesendet werden müssen
#define MASK 	0b00011111

void initSPI();

uint16_t ADC_receive();

void send_config(uint8_t config);

uint8_t receive_data();