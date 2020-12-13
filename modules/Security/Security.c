/************************************************************************
 * File Name          : Security.c
 * Author             : author
 * Date               : 09/06/2020
 * Description        :
 ***********************************************************************/

/************************************************************************
 * INCLUDES                                                             *
 ************************************************************************/
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_type.h"
#include "stm32f10x_tim.h"

#include "Task.h"
#include "Task_cfg.h"
#include "Security.h"

/************************************************************************
 * DEFINES                                                              *
 ************************************************************************/
#define SEC_TYPE_LOCK       0
#define SEC_TYPE_VOLET      1
#define SEC_TYPE_OTHER      2

#define SEC_ID_INVALID      255

#define MAX_SECURITY_DEVICE_NUM     2

#define SECURITY_DOOR_OPEN      0
#define SECURITY_DOOR_CLOSE     1
#define SECURITY_DOOR_PULSE     2
#define SECURITY_PORTAIL_OPEN   3
#define SECURITY_PORTAIL_CLOSE  4
#define SECURITY_GET_STATE      5


/************************************************************************
 * GLOBAL VARIABLES                                                     *
 ************************************************************************/
typedef struct
{
    /* Config */
    unsigned char type;
    unsigned char outputPort;
    unsigned char outputPin;
    unsigned char timer;
    unsigned char linkedId;
    unsigned char deviceName[30];

    /* State */
    unsigned char curState;
    unsigned char state;
}T_SecurityConfig;


T_SecurityConfig SecurityState[MAX_SECURITY_DEVICE_NUM]=
{
    {SEC_TYPE_LOCK, GPIOA, GPIO_Pin_4, 5/*sec*/, SEC_ID_INVALID, "Door1", 0, 0},
    {SEC_TYPE_LOCK, GPIOA, GPIO_Pin_5, 5/*sec*/, SEC_ID_INVALID, "Door2", 0, 0},
};

/************************************************************************
 * FUNCTIONS                                                            *
 ************************************************************************/


/************************************************************************
 * Function: Security_Init                                              *
 * input   : none                                                       *
 * output  : none                                                       *
 * return  : none                                                       *
 * description: Initialize the Security module                          *
 ***********************************************************************/
void Security_Init(void)
{
    unsigned char i;

    for(i=0; i<MAX_SECURITY_DEVICE_NUM ;i++)
    {
        SecurityState[i].curState = 0;
        SecurityState[i].state = 0;
    }
}

/************************************************************************
 * Function: Security_Manager                                           *
 * input   : none                                                       *
 * output  : none                                                       *
 * return  : none                                                       *
 * description: Intercom module main function                           *
 ***********************************************************************/
void Security_Mainfunction(void)
{
  unsigned char i;
  for(i=0; i<MAX_SECURITY_DEVICE_NUM ;i++)
  {
    if( (SecurityState[ElemId].state>0) && (SecurityState[ElemId].state<255) )
    {
        SecurityState[ElemId].state--;
        if(SecurityState[ElemId].state == 0)
        {
            //TODO: reset output
        }
    }
  }
}


/************************************************************************
 * Function: SecurityOrderTmt                                           *
 * input   : ElemId                                                     *
 *           Order                                                      *
 *           *param                                                     *
 * output  : none                                                       *
 * return  : status                                                     *
 * description: Intercom module main function                           *
 ***********************************************************************/
unsigned char SecurityOrderTmt( unsigned char ElemId, unsigned char Order, unsigned char *param )
{
    unsigned char retVal=1;

    switch( Order )
    {
        case SECURITY_DOOR_OPEN:
        {
            if( SecurityState[ElemId].state == 0 )
            {
                SecurityState[ElemId].state = 255;
                retVal = 0;
            }
        }
        break;

        case SECURITY_DOOR_CLOSE:
        {
            if( SecurityState[ElemId].state != 0 )
            {
                SecurityState[ElemId].state = 0;
                retVal = 0;
            }
        }
        break;

        case SECURITY_DOOR_PULSE:
        {
            if( SecurityState[ElemId].state == 0 )
            {
                SecurityState[ElemId].state = SecurityState[ElemId].timer;
                retVal = 0;
            }
        }
        break;

        case SECURITY_PORTAIL_OPEN:
        {
            if( SecurityState[ElemId].state == 0 )
            {
                SecurityState[ElemId].state = 255;
                retVal = 0;
            }
        }
        break;

        case SECURITY_PORTAIL_CLOSE:
        {
            if( SecurityState[ElemId].state != 0 )
            {
                SecurityState[ElemId].state = 0;
                retVal = 0;
            }
        }
        break;

        case SECURITY_GET_STATE:
        {
          retVal = 0;
        }
        break;

        default:
          retVal = 1;
    }

	return retVal;
}

