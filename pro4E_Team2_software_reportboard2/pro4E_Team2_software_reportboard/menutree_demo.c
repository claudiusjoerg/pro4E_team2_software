// MenuTreeDemo.c 
//  Simple LCD menu example based on structs 
// (c) Matthias Meier
// Remark: declaring all strings using PSTR() in PROGMEM and printing by printf_P("%S") would save SRAM space...
//	but unfortunately PROGMEM isn'nt allowd in structs, so string constants would have to be declared outside them

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "board.h"
#include "menutree.h"
#include "menutree_demo.h"
#include "lcd_UNO.h"

//------------------------------------------------------------------------------
//Definition of the menu tree by declaring and initializing array variables of type MenuItem_T...

struct MenuItem_T MainMenu[] = { 
	{"Name of power plant",				nameFunc},
	{"Number of modules",				numberModules},
	{"Power Plant Status",				statusFunc},
	{"About",							aboutFunc}
};

struct MenuItem_T  SubMenuName[] = {
	{"Edit Name",						editName},
	{"Save and back to mainmenu",		backMain},			// Wie wird die Eingabe gespeichert für die Wiederverwendung?
	{"",								NULL},
	{"",								NULL}
};

struct MenuItem_T  SubMenuNumber[] = {
	{"Edit number of modules",			editModule},
	{"Save and back to mainmenu",		backMain},
	{"",								NULL},
	{"",								NULL}
};

struct MenuItem_T  SubMenuStatus[] = {
	{"Voltage of system",				voltageSys},
	{"Power of system",					powerSys},
	{"Notifications",					notesSys},
	{"Back to Mainmenu",				backMain}
};

struct MenuItem_T  SubMenuAbout[] = {
	{"Back to Mainmenu",				backMain},
	{"",								NULL},
	{"",								NULL},
	{"",								NULL}
};

//------------------------------------------------------------------------------
//Rem: in a real application, implement this and function prototypes in different module(s)

// Menu for naming power plant
void nameFunc(void)
{
	LoadMenu(SubMenuName);
}

// Edit number of modules
void numberModules(void)
{
	LoadMenu(SubMenuNumber);
} 

// Watch status about specifications
void statusFunc(void)
{
	LoadMenu(SubMenuStatus);
}
	
// Infos about product
void aboutFunc(void)
{
	LoadMenu(SubMenuAbout);
}

// Edit name of power plant
void editName(void)
{
	lcd_cursor_addr(LINE1);
	printf("Edit the name");
	lcd_cursor_addr(LINE2);
	// printf("Tool zum eingeben des Namens"); - durch drücken weiter zum nächsten Buchstaben, 8 Zeichen - nach 8x drücken bei "Save and back to mainmenu"
	lcd_cursor_addr(LINE4);
	LoadMenu(MainMenu);
}

// Changes numbers of modules
void editModule(void)
{
	printf("Number of Modules : ");
}

// Shows average voltage of power plant
void voltageSys(void)

{
	printf("Voltage of the system :");
}

// Shows average power of power plant
void powerSys(void)

{
	printf("power of the plant :");
}
	
// Shows last notifications
void notesSys(void)
{}

// Return to main menu
void backMain(void)
{
	LoadMenu(MainMenu);
}
