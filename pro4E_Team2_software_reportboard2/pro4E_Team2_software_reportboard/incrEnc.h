/* For using this header, put in the TIMER ISR and its functions

void initISR();

volatile int button = 0;

void initISR ()
{
	TCCR0B = 0b010; // Prescaler: (Bits|Prescaler) ; (001|0) ; (010|8) ; (011|64) ; (100|256) ; (101|1024)
	TIMSK0 = (1 << TOIE0);	//enable timer interrupt
	sei();
}

ISR (TIMER0_OVF_vect)
{
	check_button();
	encodeFunc();
}

*/

// Globale Variabeln
extern volatile int button;
//static int timercounter = 0;
extern volatile int enc_delta;	// -128 ... 127

// Defines
#define EncPort PORTD
#define EncPins	PIND
#define EncDDR DDRD

#define EncPIN_A 6
#define EncPIN_B 5
#define EncPIN_BT 4

#define EncPIN_LED_BT 0
#define EncPIN_LED3 3
#define EncPIN_LED2 2
#define EncPIN_LED1 1

#define BUTTON (1<<EncPIN_BT)

extern void init_encoder();
/* Initiiert den Drehgeber
*/

void check_button(void);
/* Debounce button of encoder
*/


void controlLED();
/* LEDs ansteuern
*/

void erz_enc_delta();
/* changes enc_delta of drehgeber
*/

void init_ISR();
/*init timer ISR
*/