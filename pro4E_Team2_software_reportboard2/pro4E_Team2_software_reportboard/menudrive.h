#ifndef MENUDRIVE_H
#define MENUDRIVE_H
#define MaxSize 4

#define DREHGEBER (1<<4)

#define ENC_MENU 	DREHGEBER 	// DREHGEBER used to proceed to next menu item

volatile int value2;

//------------------------------------------------------------------------------

//menu function type (a parameterless function with return value int)
typedef void (*Menufunc_T)(void);

// menu data type (a struct with text to show plus corresponding menu function)
struct MenuItem_T
{
	char * text;
	Menufunc_T func;
};

// global variables (normally not used)
struct MenuItem_T * activeMenu;
int activeMenuItem;


// macro to easy load a new menu
#define LoadMenu(menu) _LoadMenu(menu, NrArrayItems(menu));

// function to Process the Menu when a button is pushed
void ProcessMenu(char button);

//---------------------------------------------------------

//internal function to load a new menu
void _LoadMenu(struct MenuItem_T menu[MaxSize], int nrMenuItems);

//Macro to estimate the number of items in a menu
#define NrArrayItems(array) (sizeof(array)/sizeof(array[0]))

#endif //MENUDRIVE_H