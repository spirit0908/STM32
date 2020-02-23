
#include "LcdMenu.h"
#include "n3310.h"


T_DisplayItemInfo CurMenuItem;

#define MENULISTMAX 12

T_MenuList MenuList[MENULISTMAX] =
{
        {0, "Menu 1", NULL},
            {1, "Menu 1.1", NULL},
            {1, "Menu 1.2", NULL},
        {0, "Menu 2", NULL},
            {1, "Menu 2.1", NULL},
            {1, "Menu 2.2", NULL},
                {2, "Menu 2.2.1", NULL},
                    {3, "Menu 2.2.1.1", NULL},
        {0, "Menu 3", NULL},
            {1, "Menu 3.1", NULL},
        {0, "Menu 4", NULL},
        {0, "Menu 5", NULL},
};

unsigned char curItemId=0;
unsigned char curItemLevel=0;

unsigned char curseur[10]={0};
unsigned char firstItemId[10]={0};


void LcdMenu_Init(void)
{
    unsigned char i;

    curItemId=0;
    curItemLevel=0;

    for(i=0; i<10; i++)
    {
        curseur[i]=0;
        firstItemId[i]=0;
    }
}

unsigned char FindNextItem(unsigned char tempItemId)
{
    unsigned char level;

    //Get level
    if(tempItemId < MENULISTMAX )
    {
        level = MenuList[tempItemId].ItemLevel;
        tempItemId++;
    }
    else
    {
        tempItemId = 0xFF;
    }

    while( tempItemId < MENULISTMAX )
    {
        if( MenuList[tempItemId].ItemLevel == level )
        {
            //This is the next elem of the menu. break and return this ID
            break;
        }
        else if(MenuList[tempItemId].ItemLevel > level)
        {
            //This is a sub element of this menu.
            //Ignore and continue loop
            tempItemId++;
        }
        else
        {
            //This is a upper menu. There is no other element in this menu.
            //return an invalid value.
            tempItemId = 0xFF;
            break;
        }
    };

    return tempItemId;
}

unsigned char FindPreviousItem(unsigned char tempItemId)
{
    unsigned char level;
    level = MenuList[tempItemId].ItemLevel;

    while( tempItemId > 0 )
    {
        tempItemId--;

        if( MenuList[tempItemId].ItemLevel == level )
        {
            break;
        }
        else if( MenuList[tempItemId].ItemLevel > level )
        {
            //sub menu. do nothing
        }
        else
        {
            //Sub menu. No more item in the current level.
            tempItemId = 0xFF;
            break;
        }
    }

    return tempItemId;
}

void LcdMenu_Display(void)
{
    unsigned char itemLevel = MenuList[curItemId].ItemLevel;
    unsigned char ItemId = firstItemId[itemLevel];
    unsigned char curseurPos = curseur[itemLevel];
    unsigned char line;

    LcdClear();

    LcdGotoXYFont(0,0);
    LcdStr(FONT_1X, (unsigned char*)"Main menu" );

    LcdGotoXYFont(0,1);
    LcdStr(FONT_1X, (unsigned char*)"--------------" );

    for(line=0; line<4; line++)
    {
        if( ItemId<MENULISTMAX )
        {
            LcdGotoXYFont(0,2+line);
            if(curseur[itemLevel] == line)
            {
                LcdStr(FONT_1X, (unsigned char*)">" );
            }
            else
            {
                LcdStr(FONT_1X, (unsigned char*)" " );
            }
            LcdGotoXYFont(1,2+line);
            LcdStr(FONT_1X, (unsigned char*)MenuList[ItemId].ItemName );
        }
        ItemId = FindNextItem(ItemId);
    }

    LcdUpdate();
}

unsigned char LcdMenu_MenuDown(void)
{
    unsigned char nextItemId;
    unsigned char level = MenuList[curItemId].ItemLevel;

    nextItemId = FindNextItem(curItemId);

    if( nextItemId < MENULISTMAX)
    {
        curItemId = nextItemId;

        if( curseur[level] < 3 )
        {
            //Move the cursor
            curseur[level] ++;
        }
        else
        {
            //Shift the menu. Update the firstItemId
            firstItemId[level]= FindNextItem(firstItemId[level]);
        }
    }

    LcdMenu_Display();
    return 0;
}

unsigned char LcdMenu_MenuUp(void)
{
    unsigned char previousItemId;
    unsigned char level = MenuList[curItemId].ItemLevel;

    previousItemId = FindPreviousItem(curItemId);

    if( previousItemId < MENULISTMAX)
    {
        //The next menu item exists.
        if( curseur[level] > 0 )
        {
            curseur[level]--;
            curItemId = previousItemId;
        }
        else
        {
            //Shift the menu. Update the firstItemId
            firstItemId[level] = previousItemId;
            curItemId = previousItemId;
        }
    }

    LcdMenu_Display();
    return 0;
}

unsigned char LcdMenu_MenuRight(void)
{
    unsigned char level;
    unsigned char newItemId;

    newItemId = curItemId+1;

    if( newItemId < MENULISTMAX )
    {
        level=MenuList[newItemId].ItemLevel;

        if( level > MenuList[curItemId].ItemLevel )
        {
            firstItemId[level]=newItemId;
            curItemId = newItemId;
            curItemLevel = level;

            curseur[level]=0;
        }
        else
        {
            //callback function
        }
    }
    else
    {
        //callback function
    }

    LcdMenu_Display();
    return 0;
}

unsigned char LcdMenu_MenuLeft(void)
{
    unsigned char tempItemId;

    tempItemId = curItemId;

    if( curItemLevel > 0 )
    {
        //Find parent item
        while( tempItemId > 0 )
        {
            tempItemId--;

            if( MenuList[tempItemId].ItemLevel < curItemLevel)
            {
                curItemLevel = MenuList[tempItemId].ItemLevel;
                curItemId = tempItemId;
                break;
            }
        }
    }

    LcdMenu_Display();
    return 0;
}

