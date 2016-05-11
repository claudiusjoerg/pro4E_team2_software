#include "encoder.h"


volatile int push=0;
volatile int rot=0;
signed int count =0;
volatile int cFlag=0;

volatile int menu=1;
volatile int inc_jump=0;


void enc_init(void){
	DDRD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));		//set pins to input
	EICRA |= (1 << ISC01)|(1 << ISC10);   		 // trigger on falling edge INT0 and INT1
	EIMSK |= (1 << INT0)|(1 << INT1);   	  	// Turns on INT0, INT1
}
 
//Taster
ISR (INT0_vect){
	klick();
}


//Drehknopf
ISR (INT1_vect){
	
	if(ENC_A) cFlag=1;
	
	//Drehrichtung bestimmen
	if(!ENC_A && cFlag){
		if(ENC_B) count++;
		else count--;
		cFlag=0;
		beep();
	}
	
	//Wechsel in Menu bei Bewegung
	if(menu==1)menu=0;
	inc_jump=0;
}

signed int get_count(){
	return count;
}

void set_count(int c){
	count=c;	
}

void clear_count(){
	count=0;
}


signed int enc_counter(void){
	if(ENC_B)
	return -1;
	else
	return 1;
	
}

