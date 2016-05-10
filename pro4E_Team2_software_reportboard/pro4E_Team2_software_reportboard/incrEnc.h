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

void init_encoder();
/* Initiiert den Drehgeber
*/

static void check_button(void);
/* Debounce button of encoder
*/

void encodeFunc();
/* For encoding the encoder
*/