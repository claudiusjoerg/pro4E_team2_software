#ifndef MENUTREEDEMO_H
#define MENUTREEDEMO_H

//------------------------------------------------------------------------------
// menu text and and prototype function for example menu (implemented in menutree_demo.c)

void nameFunc(void);
void numberModules(void);
void statusFunc(void);
void aboutFunc(void);
void editModule(void);
void voltageSys(void);
void powerSys(void);
void notesSys(void);
void backMain(void);
void editName(void);

//void MF_LoadmenuMain(void);
//static char read_buttons(void);

//------------------------------------------------------------------------------
// Global structs for external use

extern struct MenuItem_T MainMenu[4];
/**/
extern struct MenuItem_T  SubMenuName[2];
/**/
extern struct MenuItem_T  SubMenuNumber[2];
/**/
extern struct MenuItem_T  SubMenuStatus[4];
/**/
extern struct MenuItem_T  SubMenuAbout[1];
/**/

#endif //MENUTREEDEMO_H