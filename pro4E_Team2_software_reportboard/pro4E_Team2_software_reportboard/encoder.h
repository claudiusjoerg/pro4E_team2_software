#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

#define ENC_A (PIND & 1<<PD3)
#define ENC_B (PIND & 1<<PD4)
#define TASTER (PIND & 1<<PD2)

extern volatile int push;
extern volatile int rot;

extern volatile int menu;
extern volatile int inc_jump;

void enc_init(void);
int enc_counter(void);
void clear_count();
void set_count(int c);
signed int get_count();
