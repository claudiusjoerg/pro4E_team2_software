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
//extern volatile int button;
//extern volatile int enc_delta;	// -128 ... 127
extern volatile int i;

// Defines
#define EncPort PORTD
#define Encpins PIND
#define EncDDR DDRD

#define EncPIN_A		3
#define EncPIN_B		4
#define EncPIN_BT		(1<<2)
#define EncPIN_LED_BT	0
#define EncPIN_LED3		6
#define EncPIN_LED2		5
#define EncPIN_LED1		1
#define EncPIN_ALLLED	(1<<EncPIN_LED3)|(1<<EncPIN_LED2)|(1<<EncPIN_LED1)

#define PUSHBUTTON EncPIN_BT
#define MENUDOWN	(1<<EncPIN_A)
#define MENUUP		(1<<EncPIN_B)

extern void init_encoder();
/* Initiiert den Drehgeber
*/

void erz_enc_delta();
/* changes encdelta of drehgeber
*/

extern int encode_read_encdelta(void);
/**/

extern int encode_read_button(void);
/**/

extern void init_ISR();
/*init timer ISR
*/