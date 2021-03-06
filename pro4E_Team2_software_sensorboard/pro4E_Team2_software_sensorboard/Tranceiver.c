#include "Tranceiver.h"

void init_Tranceiver(){
	//Einstellungen UART
	uart_init(2400);
	PORTC=(1<<PORTC4);//Choose UART
	
	//Transmission Mode
	//REG_DATA Hardwaremässig auf Ground
	PORTC |= (0<<PORTC6); //RxDx = 0
	
	//Datenpin aktivieren
	DDRD = 0b00000010; //TxD = 1
}

void uebertragung_uart() {
	//Daten Input vom ADC
	 uint8_t data = ADC_receive();
	//data = mittelwert(data);

	//char *buffer = "Not implemented";
	for (int i=0; i<8; i++)
	{

	 /*
     *  Transmit string to UART
     *  The string is buffered by the uart library in a circular buffer
     *  and one character at a time is transmitted to the UART using interrupts.
     *  uart_puts() blocks if it can not write the whole string to the circular 
     *  buffer
     */
    uart_putc(data);
	
	 /*
         * Get received character from ringbuffer
         * uart_getc() returns in the lower byte the received character and 
         * in the higher byte (bitmask) the last receive error
         * UART_NO_DATA is returned when no data is available.
         *
         */
		int bit = uart_getc();
		
        if ( bit & UART_NO_DATA )
        {
            /* 
             * no data available from UART 
             */
        }
        else
        {
            /*
             * new data available from UART
             * check for Frame or Overrun error
             */
            if ( bit & UART_FRAME_ERROR )
            {
                /* Framing Error detected, i.e no stop bit detected */
                uart_puts_P("UART Frame Error: ");
            }
            if ( bit & UART_OVERRUN_ERROR )
            {
                /* 
                 * Overrun, a character already present in the UART UDR register was 
                 * not read by the interrupt handler before the next character arrived,
                 * one or more received characters have been dropped
                 */
                uart_puts_P("UART Overrun Error: ");
            }
            if ( bit & UART_BUFFER_OVERFLOW )
            {
                /* 
                 * We are not reading the receive buffer fast enough,
                 * one or more received character have been dropped 
                 */
                uart_puts_P("Buffer overflow error: ");
            }
            /* 
             * send received character back
             */
            uart_putc( (uint8_t )bit );
		}
	}
}