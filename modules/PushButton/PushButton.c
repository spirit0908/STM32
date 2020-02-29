/************************************************************************
 * File Name          : PushButton.c
 * Author             : author
 * Date               : 12/02/2017
 * Description        :
 ***********************************************************************/


/************************************************************************
* INCLUDES *
************************************************************************/
#include "stm32f10x_lib.h"
#include "stm32f10x_map.h"
#include "stm32f10x_gpio.h"
#include "teleinfo.h"
#include "PushButton.h"
#include "LcdMenu.h"



/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
PB_Config_T PushButtonConfig[PB_CONFIG_NB] =
{
    {/*"PB_UP",*/    GPIOA, GPIO_Pin_0,  &LcdMenu_MenuUp,    &LcdMenu_MenuTop, NULL, PB_IDLE, 0},
    {/*"PB_LEFT",*/  GPIOC, GPIO_Pin_15, &LcdMenu_MenuLeft,  NULL, NULL, PB_IDLE, 0},
    {/*"PB_DOWN",*/  GPIOC, GPIO_Pin_14, &LcdMenu_MenuDown,  NULL, NULL, PB_IDLE, 0},
    {/*"PB_RIGHT",*/ GPIOA, GPIO_Pin_1,  &LcdMenu_MenuRight, NULL, NULL, PB_IDLE, 0}
};

/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: PushButton_Mgt                                             *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Main function of PushButton module                      *
 ***********************************************************************/
unsigned char PushButton_Mgt(void)
{
    unsigned char PBState, i;
        
    for(i=0; i<PB_CONFIG_NB; i++)
    {
        PBState = GPIO_ReadInputDataBit(PushButtonConfig[i].GPIO_Port, PushButtonConfig[i].GPIO_Pin);

        switch (PushButtonConfig[i].curState)
        {
            case PB_IDLE:
            {
                if(PBState)
                {
                    PushButtonConfig[i].push_cpt=0;
                    PushButtonConfig[i].curState = PB_PUSHED;
                }
            }
            break;

            case PB_PUSHED:
            {
                if(PBState)
                {
                    if(PushButtonConfig[i].push_cpt < 255)
                    {
                        PushButtonConfig[i].push_cpt++;
                    }
                }
                else
                {
                    if(PushButtonConfig[i].push_cpt > CONFIG_PUSH_CPT)
                    {
                        PushButtonConfig[i].curState = PB_CONFIG_PUSH;
                    }
                    else if(PushButtonConfig[i].push_cpt > LONG_PUSH_CPT)
                    {
                        PushButtonConfig[i].curState = PB_LONG_PUSH;
                    }
                    else
                    {
                        PushButtonConfig[i].curState = PB_SHORT_PUSH;
                    }
                }
            }
            break;

            case PB_SHORT_PUSH:
            {
                if(PushButtonConfig[i].SP_action != NULL)
                {
                    (PushButtonConfig[i].SP_action)();
                }

                PushButtonConfig[i].curState = PB_IDLE;
            }
            break;

            case PB_LONG_PUSH:
            {
                if(PushButtonConfig[i].LP_action != NULL)
                {
                    (PushButtonConfig[i].LP_action)();
                }
                PushButtonConfig[i].curState = PB_IDLE;
            }
            break;

            case PB_CONFIG_PUSH:
            {
                if(PushButtonConfig[i].CP_action != NULL)
                {
                    (PushButtonConfig[i].CP_action)();
                }
                PushButtonConfig[i].curState = PB_IDLE;
            }
            break;

            default:
                PushButtonConfig[i].curState = PB_IDLE;
            break;
        }
    }
    return 0;
}

