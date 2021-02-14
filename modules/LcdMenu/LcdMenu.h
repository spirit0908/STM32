/************************************************************************
 * File Name          : LcdMenu.h
 * Author             :
 * Date               : 12/02/2017
 * Description        : LcdMenu header file
 ***********************************************************************/

#ifndef LCDMENU_H
#define LCDMENU_H

/************************************************************************
* INCLUDES *
************************************************************************/


/************************************************************************
* DEFINES *
************************************************************************/
#define NULL    0


/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct
{
    unsigned char ItemLevel;
    unsigned char ItemName[12];
    unsigned char (*pf)();  // pointer to task
} T_MenuList;

typedef struct
{
    unsigned char ItemId;
    unsigned char firstItemId; //First item to display in the menu
    unsigned char cursorPos;    // Position of the cursor (from 0 to LASTLINE)
} T_DisplayItemInfo;


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void LcdMenu_Init();

unsigned char FindFirstItem(unsigned char ItemId);
unsigned char FindNextItem(unsigned char tempItemId);
unsigned char FindPreviousItem(unsigned char tempItemId);

void LcdMenu_Display(void);

unsigned char LcdMenu_MenuTop(void);
unsigned char LcdMenu_MenuDown(void);
unsigned char LcdMenu_MenuUp(void);
unsigned char LcdMenu_MenuRight(void);
unsigned char LcdMenu_MenuLeft(void);


#endif  /* TASK_H */

