

#include "Light.h"
//#include "Fifo.h"
//#include "def.h"
#include "Std_Types.h"

T_LightConfig LightConfig[MAX_LIGHT_NUM]=
{
    // port - pin -
    {GPIOA, GPIO_Pin_4},
    {GPIOA, GPIO_Pin_5},
};

//T_LightState LightState[MAX_LIGHT_NUM]=
//{
//    // light state
//    {0},
//    {0}
//};

T_LightState LightState[MAX_LIGHT_NUM]=
{
    /*type | outPin|curState|state|brightness_default|brightness_last|timer_default|timer_val|Current timer value*/
    {{0}, 0},
    {{0}, 0},
//	{0b10100000, 0, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0}, // RELAY 1
//	{0b10100000, 1, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0}, // RELAY 2
////	{0b10100000, 2, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0},
////	{0b10100000, 3, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0}
};


/* CFG */

//LightDesc[]=
//{
//		{
//				type: dimmable / RGB /
//		},
//};


void Light_Init(void)
{
    unsigned char i;
    
    for(i=0u; i<MAX_LIGHT_NUM; i++)
    {
        LightState[i].type.active  	= 1u; /*LIGHT_TYPE_ACTIVE;*/
        LightState[i].type.dimmable = 0u; /*LIGHT_TYPE_ACTIVE;*/
        LightState[i].type.timer  	= 1u; /*LIGHT_TYPE_ACTIVE;*/
        LightState[i].type.ledStrip = 1u; /*LIGHT_TYPE_ACTIVE;*/

        //LightState[i].outPin;
        //LightState[i].curState;             // State/Brightness of current output: form 00 (OFF) to FF (MAX).

    	LightState[i].state = 0u;
//        LightState[i].curState=0u;
//        LightState[i].brightness_last=0u;
//        LightState[i].timer_val=0u;

        //LightState[i].brightness_default;   // default brightness value
        //LightState[i].brightness_last;      // last brightness value recorded
        //LightState[i].timer_default;        // default timer value
        //LightState[i].timer_val;            // Current timer value
    }
}


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

unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned char *param )
{
    unsigned char brightness;
    unsigned char ret_value=ret_OK;
    
    if( LightId > MAX_LIGHT_NUM )
    {
        return ret_NOK;
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
//            return ret_OK;
//        }
//    }

    switch( Order )
    {
        case LIGHT_OFF:
//            if( LightState[LightId].state > 0)
//            {
//                // Store the current state to be able to reuse it on the next ON order
//                LightState[LightId].brightness_last = LightState[LightId].state;
//            }
//            // Reset the timer and set the state to OFF:
//            LightState[LightId].timer_val = 0;
            LightState[LightId].state = 0;
        break;
        
        case LIGHT_ON:
            // Reset any timer
//            LightState[LightId].timer_val = 0x0000;

            if( LightState[LightId].state == 0 )
            {
                // If the light state was OFF before, switch it to on at the max brightness
                LightState[LightId].state = 0xFF;
            }
            else if( LightState[LightId].state == 0xFF)
            {
                // Light was already ON at max brightness. Nothing more to do.
            }
            else //( LightState[OutputNum-1].state > 0 && LightState[OutputNum-1].state < 0xFF )
            {
//                // Light brightness was not at max, so save it for next dimmable use
//                LightState[LightId].brightness_last = LightState[LightId].state;
//
//                // Set maximum brightness
                LightState[LightId].state = 0xFF;
            }
        break;

        case LIGHT_REVERSE:
            if ( LightState[LightId].state )
            {
                // Light is ON
                // Store the current brightness and switch it OFF.
//                LightState[LightId].brightness_last = LightState[LightId].state ;
                LightState[LightId].state = 0;
            }
            else
            {
                // Light is OFF
//                if( LightState[LightId].type == LIGHT_TYPE_DIMMABLE)
//                {
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
//                }
//                else
//                {
                    LightState[LightId].state = 0xFF;
//                }
            }
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
            ret_value = ret_NOK;
        break;
    }

	return ret_value;
}


/*void LightOrderProcess(void)
{
    unsigned char i;
    unsigned char pinnum, pinstate;
    
//    for( i=0; i<MAX_LIGHT_NUM; i++)
//    {
//        if( LightState[i].curState != LightState[i].state)
//        {
//            pinnum = LightState[i].outPin;
//            pinstate = LightState[i].state;
//            //IOsetState( &PinMapping[pinnum], pinstate);
//
//            LightState[i].curState = LightState[i].state;
//            LightSendOutputStatus(i);
//        }
//    }
}*/

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
        
void LightSendOutputStatus(unsigned char i)
{
    unsigned char pinnum, pinstate;
    unsigned char msg[8];
    
//    msg[0]=OWN_CAN_ID;
//    msg[1]=i;
//    msg[2]=LightState[i].state;
//
//    CAN_FIFO_add(&CAN_TX_FIFO, CAN_ID_BROADCAST, 3, msg);
}

