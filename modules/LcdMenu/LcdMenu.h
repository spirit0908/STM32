/* 
 * File:   Task.h
 * Author:
 *
 * Created on 12 f�vrier 2017, 21:50
 */

#ifndef LCDMENU_H
#define LCDMENU_H

#ifdef  __cplusplus
extern "C" {
#endif

#define NULL 0

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

void LcdMenu_Init();
unsigned char FindNextItem(unsigned char tempItemId);
unsigned char FindPreviousItem(unsigned char tempItemId);
void LcdMenu_Display(void);
unsigned char LcdMenu_MenuDown(void);
unsigned char LcdMenu_MenuUp(void);
unsigned char LcdMenu_MenuRight(void);
unsigned char LcdMenu_MenuLeft(void);


#ifdef  __cplusplus
}
#endif

#endif  /* TASK_H */

