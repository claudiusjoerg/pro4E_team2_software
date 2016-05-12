/* menutree.c
 * Simple LCD menu example based on structs 
 * (c) Matthias Meier, 2015
 */

#include <stdio.h>
#include "menutree.h"
#include "menutree_demo.h"
#include "board.h"
#include "lcd_UNO.h"
#include "incrEnc.h"

struct MenuItem_T * activeMenu;									//same as: static struct MenuItem_T activeMenu[];
int activeMenuItem;
static int nrMenuItems;
volatile int8_t menu_Max = 4;


/**
  * _LoadMenu() - load another menu tree (main- or submenu)
 */
void _LoadMenu(struct MenuItem_T menu[], int nrItems)
{
		activeMenu = menu;
		nrMenuItems = nrItems;
		activeMenuItem = 0;
		ProcessMenu(0);											// Display first menuitem (on first display line)
}

/**
  * ProcessMenu() - change to next or execute current menu item, then display menu text
 */
void ProcessMenu(char button)
{
	switch (button){
		
	case ENC_MENU:
		if (enc_delta < 0)
		{
			if (-enc_delta > activeMenuItem)
			{
				activeMenuItem = 0;
			}else activeMenuItem +=enc_delta;
		}
		else{
			if (enc_delta >(menu_Max-activeMenuItem))
			{activeMenuItem = menu_Max;
			}
			 else activeMenuItem +=enc_delta;
		}
		//activeMenuItem = (activeMenuItem + 1) % nrMenuItems;	//proceed to next menu item
		break;

	case BUTTON_EXECUTE:
		if (activeMenu[activeMenuItem].func!=NULL)  
			activeMenu[activeMenuItem].func();					//execute the selected menufunction
	}
	lcd_cursor_addr(LINE1);
	printf("%s",activeMenu[activeMenuItem].text);				//display current selected menu text
	lcd_cursor_addr(LINE2);
	printf("%s",activeMenu[activeMenuItem+1].text);	
	lcd_cursor_addr(LINE3);
	printf("%s",activeMenu[activeMenuItem+2].text);	
	lcd_cursor_addr(LINE4);
	printf("%s",activeMenu[activeMenuItem+3].text);	
}



