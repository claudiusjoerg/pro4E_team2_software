#ifndef MENUCONTENT_H
#define MENUCONTENT_H

//------------------------------------------------------------------------------
// menu text and and prototype function for example menu (implemented in menutree_demo.c)

void settingfunc(void);
void statusFunc(void);
void aboutFunc(void);
void editNumber(void);
void editName(void);
void voltageSys(void);
void notesSys(void);
void backMain(void);

//void MF_LoadmenuMain(void);
//static char read_buttons(void);

//------------------------------------------------------------------------------
// Global structs for external use

extern struct MenuItem_T	MainMenu[3];

extern struct MenuItem_T	SubMenuSetting[3];

extern struct MenuItem_T	SubMenuStatus[3];

extern struct MenuItem_T	SubMenuAbout[4];

#endif //MENUCONTENT_H