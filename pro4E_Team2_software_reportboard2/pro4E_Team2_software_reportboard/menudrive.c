/* menutree.c
 * Simple LCD menu example based on structs 
 * (c) Matthias Meier, 2015
 */

#include <stdio.h>
#include "menudrive.h"
#include "menucontent.h"
#include "lcd_UNO.h"
#include "encoder.h"

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
		
	/*	auskommentiert von Claudius für Code testen von Yohannes*/
	case MENUDOWN:
		activeMenuItem = (activeMenuItem + 1) % nrMenuItems;	//proceed to next menu item
		break;
		
	case MENUUP:
		activeMenuItem--;
		if (activeMenuItem < 0)
		{
			activeMenuItem += nrMenuItems;
		}
		break;
	
	/*das ist der Code zum testen von Yohannes
	case ENC_MENU:
		if (value2 < 0)
		{
			if (-value2 > activeMenuItem)
			{
				activeMenuItem = 0;
			}else activeMenuItem +=value2;
		}
		else{
			if (value2 >(menu_Max-activeMenuItem))
			{
				activeMenuItem = menu_Max;
			}
			else activeMenuItem +=value2;
		}
		break;*/
	//**********************************************
	case PUSHBUTTON:											// linked to button of encoder
		if (activeMenu[activeMenuItem].func!=NULL)  
			activeMenu[activeMenuItem].func();					// execute the selected menufunction
		break;
	}
	/*das ist der Code zum testen von Yohannes*/
	for (int i=0; i<nrMenuItems; i++)
	{
		switch(i){
			case 0:
			lcd_cursor_addr(LINE1);
			break;
			case 1:
			lcd_cursor_addr(LINE2);
			break;
			case 2:
			lcd_cursor_addr(LINE3);
			break;
			case 3:
			lcd_cursor_addr(LINE4);
			break;
		}
		if (activeMenuItem == i) {
			printf("-");
			} else {
			printf(" ");
		}
		printf("%s",activeMenu[i].text);
	}
	//**********************************************
	/* auskommentiert von Claudius für Code testen von Yohannes
	clear();													// clear lcd
	printf("%s", activeMenu[activeMenuItem].text);				// display current selected menu text
	*/
}



