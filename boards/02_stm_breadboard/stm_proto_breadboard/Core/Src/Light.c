/************************************************************************
 * File Name          : Light.c
 * Author             :
 * Date               : 11/02/2017
 * Description        :
 ***********************************************************************/

/************************************************************************
* INCLUDES *
************************************************************************/
//#include "def.h"
#include "Light.h"
#include "Std_Types.h"
//#include "Fifo_Cfg.h"
#include "main.h"

/************************************************************************v
* DEFINES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
T_LightConfig LightConfig[MAX_LIGHT_NUM]=
{
    /* Port | Pin | type */
    { GPIOB , GPIO_PIN_13, 0b00001000, 0, 0 },
    { GPIOB , GPIO_PIN_14, 0b00001000, 0, 0 },
    { GPIOB , GPIO_PIN_15, 0b00001000, 0, 0 }
};

T_LightState LightState[MAX_LIGHT_NUM]=
{
    /* state | order */
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};


/************************************************************************
* PRIVATE PROTOTYPES *
************************************************************************/


/************************************************************************
* FUNCTIONS *
************************************************************************/


/************************************************************************
 * Function: Light_Init                                                 *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Initialize the Light module                             *
 ***********************************************************************/
void Light_Init(void)
{
    unsigned char i;
    
    for(i=0u; i<MAX_LIGHT_NUM; i++)
    {
        LightState[i].state = 0u;
        LightState[i].order = 0u;
        LightState[i].timer_val=0u;

        LightOutputReset(i);

//      LightState[i].brightness_last = LightConfig[i].brightness_default;      // last brightness value recorded
//      LightState[i].timer_val = LightConfig[i].timer_default;
    }
}

/************************************************************************
 * Function: Light_Init_cfg                                             *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Initialize the configuration part of the Light module   *
 ***********************************************************************/
void Light_Init_cfg(void)
{
    //Light output 0
//    LightState[0].timer_default=0u;
//    LightState[0].brightness_default=12u;
//    LightState[0].outPin=0;
//    LightState[0].type = 0b10100000;
    // type of output is:
    // - bit 7: 0: output is inactive / 1: output is active
    // - bit 6: 0: output is not dimmable / 1:output is dimmable
    // - bit 5: 0: timer can not be set / 1: timer can be set
    // - bit 4-0: NA
//    LightState[0].timer_default=0xFF;        // default timer valued
    
    // Light output 1
//    LightState[1].timer_default=0u;
//    LightState[1].brightness_default=0xFFu;
//    LightState[1].outPin=1;
//    LightState[1].type = 0b10100000;
//    LightState[1].timer_default=0xFF;
    
//    // Light output 2
//    LightState[2].timer_default=0u;
//    LightState[2].brightness_default=0xFFu;
//    LightState[2].outPin=2;
//    LightState[2].type = 0b10100000;
//    LightState[2].timer_default=0xFF;
//
//    // Light output 3
//    LightState[3].timer_default=0u;
//    LightState[3].brightness_default=0xFFu;
//    LightState[3].outPin=3;
//    LightState[3].type = 0b10100000;
//    LightState[3].timer_default=0xFF;
}

/************************************************************************
 * Function: LightOrderTmt                                              *
 * input: LightId                                                       *
 *        Order                                                         *
 *        param                                                         *
 * output: none                                                         *
 * return:                                                              *
 * description:                                                         *
 ************************************************************************/
unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned int value )
{
    unsigned char ret = LIGHT_E_OK;
    (void) value;

    if( LightId >= MAX_LIGHT_NUM )
    {
        return LIGHT_E_INVALID_LIGHTID;
    }
    
//    if( (LightState[LightId].type & LIGHT_TYPE_ACTIVE) == 0 ) // check if output is inhibited
//    {
//        if( Order == LIGHT_RELEASE_OUTPUT)
//        {
//            LightState[LightId].type |= LIGHT_TYPE_ACTIVE;
//            return ret_OK;
//        }
//        else
//        {
//            return ret_not_OK;
//        }
//    }


    switch( Order )
    {
        case LIGHT_OFF:
            ret = Light_order_LightOff(LightId);
        break;
        
        case LIGHT_ON:
            ret = Light_order_LightOn(LightId);
        break;

        case LIGHT_REVERSE:
            ret = Light_order_LightReverseState(LightId);
        break;

//        case LIGHT_ON_LAST_BRIGHTNESS:
//            LightState[LightId].state = LightState[LightId].brightness_last;
//            LightState[LightId].timer_val = 0;
//        break;
//
//        case LIGHT_ON_SPECIFIED_BRIGHTNESS:
//            brightness = param;
//
//            if( LightState[LightId].type & LIGHT_TYPE_DIMMABLE )
//            {
//                LightState[LightId].timer_val = 0;
//                if( brightness > 0 )
//                    LightState[LightId].state = brightness;
//            }
//        break;
//
//        case LIGHT_ON_DEFAULT_BRIGHTNESS:
//            if( LightState[LightId].type & LIGHT_TYPE_DIMMABLE )
//            {
//                if( LightState[LightId].state > 0 )
//                {
//                    LightState[LightId].state = LightState[LightId].brightness_default;
//                    LightState[LightId].timer_val = 0;
//                }
//            }
//        break;
//
//        case LIGHT_BRIGHTNESS_MORE:
//            if( LightState[LightId].type & LIGHT_TYPE_DIMMABLE )
//            {
//                if( LightState[LightId].state > 0 )
//                {
//                    //Light is already ON. Add brightness if max value is not reached
//                    if( LightState[LightId].state < 10 )
//                        LightState[LightId].state += 1;
//                }
//                else
//                {
//                    // Light was OFF, put it on last known brightness:
//                    LightState[LightId].state = LightState[LightId].brightness_last;
//                }
//
//                // Reset any timer
//                LightState[LightId].timer_val = 0;
//            }
//        break;
//
//        case LIGHT_BRIGHTNESS_LESS:
//            if( LightState[LightId].type & LIGHT_TYPE_DIMMABLE )
//            {
//                if( LightState[LightId].state > 1 )
//                {
//                    // Brightness is more than min value. Decrease it.
//                    LightState[LightId].state -= 1;
//                }
//                else
//                {
//                    // Light is less than min accepted brightness value. Switch it OFF.
//                    LightState[LightId].state = 0x00;
//                }
//
//                // Reset any timer
//                LightState[LightId].timer_val = 0;
//            }
//        break;
//
//        case LIGHT_ON_TIMER:
//            if( LightState[LightId].state == 0 ) // Light is OFF
//            {
//                // Light was OFF, set it to max brightness
//                LightState[LightId].state = 0xFF;
//            }
//            else if( LightState[LightId].state < 10 )
//            {
//                // Light was ON but not at max. Save the current brightness for next use
//                LightState[LightId].brightness_last = LightState[LightId].state;
//            }
//            else
//            {
//                // Light was ON at max brightness. Do nothing. Timer will be started just after
//            }
//
//            // Start the timer
//            LightState[LightId].timer_val   = LightState[LightId].timer_default;
//        break;
//
//        case LIGHT_ON_TIMER_ADD_30S:
//            if( LightState[LightId].state == 0 )
//            {
//                // Light is OFF. switch it on at the default timer value.
//                LightState[LightId].timer_val== LightState[LightId].timer_default;
//                LightState[LightId].state = 0xFF;
//            }
//            else
//            {
//                // Light was already ON. Add 15s
//                // Let brightness at same value.
//                LightState[LightId].timer_val += 15;
//            }
//        break;
//
//        case LIGHT_INHIBIT_OUTPUT:
//            // type bit7
//            // Force Output to 0
//            // Switch OFF output
//            LightState[LightId].brightness_last = LightState[LightId].state;
//            LightState[LightId].state = 0x00;
//            LightState[LightId].timer_val = 0x0000;
//
//            // Disable output:
//            LightState[LightId].type &= ~(LIGHT_TYPE_ACTIVE);
//        break;
//
//        case LIGHT_RELEASE_OUTPUT:
//            // Reset light state
//            LightState[LightId].state = 0x00;
//            LightState[LightId].timer_val = 0x0000;
//
//            // Enable output:
//            LightState[LightId].type |= LIGHT_TYPE_ACTIVE;
//        break;

        default:
            ret = LIGHT_E_INVALID_ORDER;
        break;
    }

    return ret;
}

/************************************************************************
 * Function: Light_order_LightOff                                       *
 * input: LightPtr                                                      *
 * output: none                                                         *
 * return: error status                                                 *
 * description:                                                         *
 ************************************************************************/
unsigned char Light_order_LightOff(unsigned char LightId)
{
    unsigned char ret;
    T_LightState * LightPtr = &LightState[LightId];

    if(LightPtr->state > 0)
    {
        /* Store the current state to be able to reuse it on the next ON order */
        LightPtr->brightness_last = LightPtr->state;

        /* Reset the timer and set the state to OFF: */
        LightPtr->timer_val = 0;
        LightPtr->state = 0;

        /* Command GPIO */
        
//        GPIO_ResetBits(LightConfig[LightId].GPIO_Port, LightConfig[LightId].GPIO_Pin);
        LightOutputReset(LightId);

        ret = LIGHT_E_OK;
    }
    else
    {
        ret = LIGHT_E_OK;
    }

    return ret;
}

/************************************************************************
 * Function: Light_order_LightOn                                        *
 * input: LightPtr                                                      *
 * output: none                                                         *
 * return: error status                                                 *
 * description:                                                         *
 ************************************************************************/
unsigned char Light_order_LightOn(unsigned char LightId)
{
    unsigned char ret = LIGHT_E_OK;
    T_LightState * LightPtr = &LightState[LightId];

    /* Reset any timer */
    LightPtr->timer_val = 0x0000;

    if( LightPtr->state == 0 )
    {
        /* If the light state was OFF before, switch it to on at the max brightness */
        LightPtr->state = 0xFF;
//        GPIO_SetBits(LightConfig[LightId].GPIO_Port, LightConfig[LightId].GPIO_Pin);
        LightOutputSet(LightId);
    }
    else if( LightPtr->state == 0xFF)
    {
        /* Light was already ON at max brightness. Nothing more to do. */
        ret = LIGHT_E_NOK;
    }
    else /* ( LightState[OutputNum-1].state > 0 && LightState[OutputNum-1].state < 0xFF ) */
    {
        /* Light brightness was not at max, so save it for next dimmable use */
        LightPtr->brightness_last = LightPtr->state;

        /* Set maximum brightness */
        LightPtr->state = 0xFF;
 //       GPIO_SetBits(LightConfig[LightId].GPIO_Port, LightConfig[LightId].GPIO_Pin);
    }

    return ret;
}


/************************************************************************
 * Function: Light_order_LightReverseState                              *
 * input: LightPtr                                                      *
 * output: none                                                         *
 * return: error status                                                 *
 * description:                                                         *
 ************************************************************************/
unsigned char Light_order_LightReverseState(unsigned char LightId)
{
    unsigned char ret = LIGHT_E_OK;
    T_LightState * LightPtr = &LightState[LightId];

    if ( LightPtr->state )
    {
        /* Light is ON
         * Store the current brightness and switch it OFF. */
//        LightPtr->brightness_last = LightPtr->state ;
        LightPtr->state = 0;
//      GPIO_ResetBits( LightConfig[LightId].GPIO_Port, LightConfig[LightId].GPIO_Pin);

        LightOutputReset(LightId);
    }
    else
    {
        /* Light is OFF */
//        if( LightPtr->type == LIGHT_TYPE_DIMMABLE)
//        {
//            ret = LIGHT_E_NOK;
//                    // First check for last brightness
//                    if( LightState[LightId].brightness_last > 0)
//                    {
//                        // Restore the last known brightness
//                        LightState[LightId].state = LightState[LightId].brightness_last;
//                    }
//                    else
//                    {
//                        // Last brightness is unknown. Put default value and switch ON
//                        LightState[LightId].brightness_last = LightState[LightId].brightness_default;
//                    }
//
//                    // Switch it ON, at the last known brightness.
//                    LightState[LightId].state = LightState[LightId].brightness_last;
//        }
//        else
//        {
            LightPtr->state = 0xFF;
      //    GPIO_SetBits( LightConfig[LightId].GPIO_Port, LightConfig[LightId].GPIO_Pin);

            LightOutputSet(LightId);
//        }
    }

    return ret;
}

/************************************************************************
 * Function: LightSendStatus                                            *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void LightSendStatus(void)
{
    unsigned char i;
    
    for( i=0; i<MAX_LIGHT_NUM; i++)
    {
        if(LightState[i].state)
        {
            LightSendOutputStatus(i);
        }
    }
}

/************************************************************************
 * Function: LightMainFunction                                          *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void LightMainFunction(void)
{
    unsigned char i;

    for( i=0; i<MAX_LIGHT_NUM; i++)
    {
    	// send state
        LightSendOutputStatus(i);
    }


}


unsigned char LightOutputMan(void)
{

    return 0;
}

unsigned char LightOutputSet(unsigned char LightId)
{
	T_LightConfig * LightConfigPtr = &LightConfig[LightId];

	if( IS_LIGHT_TYPE_INVERTED(LightConfigPtr->type) == 0 )
	{
	   HAL_GPIO_WritePin(LightConfigPtr->GPIO_Port,
                         LightConfigPtr->GPIO_Pin,
                         GPIO_PIN_SET);
	}
	else
	{
        HAL_GPIO_WritePin(LightConfigPtr->GPIO_Port,
                          LightConfigPtr->GPIO_Pin,
                          GPIO_PIN_RESET);
	}

	return 0;
}

unsigned char LightOutputReset(unsigned char LightId)
{
	T_LightConfig * LightConfigPtr = &LightConfig[LightId];

	if( IS_LIGHT_TYPE_INVERTED(LightConfigPtr->type) == 0 )
	{
	   HAL_GPIO_WritePin(LightConfigPtr->GPIO_Port,
                         LightConfigPtr->GPIO_Pin,
                         GPIO_PIN_RESET);
	}
	else
	{
        HAL_GPIO_WritePin(LightConfigPtr->GPIO_Port,
                          LightConfigPtr->GPIO_Pin,
                          GPIO_PIN_SET);
    }

	return 0;
}

/************************************************************************
 * Function: LightSendStatus                                            *
 * input: deviceId                                                      *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void LightSendOutputStatus(unsigned char deviceId)
{
    // unsigned char pinnum;
    // unsigned char pinstate;
 //   unsigned char msg[8];
   (void) deviceId;
   /* 
    msg[0] = OWN_CAN_ID;
    msg[1] = LightState[deviceId].state;
    msg[2] = deviceId;

    CAN_FIFO_add(&CAN_TX_FIFO, CAN_ID_BROADCAST, 4, msg);
*/
}

