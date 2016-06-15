#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "menucontent.h"
#include "menudrive.h"
#include "lcd_UNO.h"

//------------------------------------------------------------------------------
//Definition of the menu tree by declaring and initializing array variables of type MenuItem_T...

struct MenuItem_T MainMenu[] = { 
	{"1.Status",	statusFunc},
	{"2.Settings",	settingfunc},
	{"3.About",		aboutFunc}
};

struct MenuItem_T  SubMenuSetting[] = {
	{"1.Edit Name",		editName},
	{"2.Edit Number",	editNumber},
	{"Back",			backMain}
};

struct MenuItem_T  SubMenuStatus[] = {
	{"1.Voltage of system",	voltageSys},
	{"2.Notifications",		notesSys},
	{"Back",				backMain}
};

struct MenuItem_T  SubMenuAbout[] = {
	{"Project 4",			contfunc},
	{"Team 2",				contfunc},
	{"Software FS16",		contfunc},
	{"Back",				backMain}
};

//------------------------------------------------------------------------------

// Menu for naming power plant
void settingfunc(void)
{
	LoadMenu(SubMenuSetting);
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

// Edit number of modules
void editNumber(void)
{
	printf("Set the number of modules");
	/*while(1)
	{
		if (1)
		{
			LoadMenu(SubMenuSetting);
		}
	}*/
} 

// Edit name of power plant
void editName(void)
{
	printf("Set a name for your plant");
	/*while(1)
	{
		if (1)
		{
			LoadMenu(SubMenuSetting);
		}
	}*/
}

// Shows average voltage of power plant
void voltageSys(void)
{
	printf("The current voltage");
	/*while(1)
	{
		if (1)
		{
			LoadMenu(SubMenuSetting);
		}
	}*/
}
	
// Shows last notifications
void notesSys(void)
{
	printf("All Notifications");
	/*while(1)
	{
		if (1)
		{
			LoadMenu(SubMenuSetting);
		}
	}*/
}

// Return to main menu
void backMain(void)
{
	LoadMenu(MainMenu);
}

// Software version and content for presentation
void contfunc(void)
{
	
}
