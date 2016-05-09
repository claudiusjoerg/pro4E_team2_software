/*
 * pro4E_Team2_software_reportboard.c
 *
 * Created: 09.05.2016 13:49
 * Author : Sarah
 */ 

#define LED1 = 0;
#define LED2 = 1;

DDRB = 0b00000011;//pins B1-B8 werden auf in- bzw. output gestellt
PORTB = 0b00000000;//startzustand fuer signal der pins einstellen
