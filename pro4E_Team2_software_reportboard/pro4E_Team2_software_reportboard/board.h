#ifndef BOARD_H
#define BOARD_H

/* Connected Hardware on Mega2560:
 * S1 = Menu-Button : Port A BitNr 4 
 * s2 = Execute Button : Port A BitNr 5
 * LED : Port A BitNr 0
 * Piezo Beeper : Port A BitNr 1
 */

#define BUTTON_S1 (1<<4)
#define BUTTON_S2 (1<<5)


#define BUTTON_PORT PORTC
#define BUTTON_PINS PINC5

#define ENC_MENU 	BUTTON_S1 	// button S1 used to proceed to next menu item

#define BUTTON_EXECUTE 	BUTTON_S2  // button S2 used to execute current active menu function

#endif // BOARD_H




