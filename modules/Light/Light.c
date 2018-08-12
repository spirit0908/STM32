
//#include "hard.h"
#include "Light.h"
#include "Fifo.h"
//#include "IO.h"
#include "def.h"

T_LightState Light_state[MAX_LIGHT_NUM]=
{
	/*type | outPin|curState|state|brightness_default|brightness_last|timer_default|timer_val|Current timer value*/
	{0b10100000, 0, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0},
	{0b10100000, 1, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0},
	{0b10100000, 2, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0},
	{0b10100000, 3, 0		, 0	  ,12				 , 12		     , 0		   , 0       , 0}
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
        Light_state[i].state=0u;
        Light_state[i].curState=0u;
        Light_state[i].brightness_last=0u;
        Light_state[i].timer_val=0u;
    }
}


void Light_Init_cfg(void)
{
    //Light output 0
    Light_state[0].timer_default=0u;
    Light_state[0].brightness_default=12u;
    Light_state[0].outPin=0;
    Light_state[0].type = 0b10100000;
    // type of output is:
    // - bit 7: 0: output is inactive / 1: output is active
    // - bit 6: 0: output is not dimmable / 1:output is dimmable
    // - bit 5: 0: timer can not be set / 1: timer can be set
    // - bit 4-0: NA
    Light_state[0].timer_default=0xFF;        // default timer valued
    
    // Light output 1
    Light_state[1].timer_default=0u;
    Light_state[1].brightness_default=0xFFu;
    Light_state[1].outPin=1;
    Light_state[1].type = 0b10100000;
    Light_state[1].timer_default=0xFF;
    
    // Light output 2
    Light_state[2].timer_default=0u;
    Light_state[2].brightness_default=0xFFu;
    Light_state[2].outPin=2;
    Light_state[2].type = 0b10100000;
    Light_state[2].timer_default=0xFF;
    
    // Light output 3
    Light_state[3].timer_default=0u;
    Light_state[3].brightness_default=0xFFu;
    Light_state[3].outPin=3;
    Light_state[3].type = 0b10100000;
    Light_state[3].timer_default=0xFF;
}

//unsigned char LightOrderTmt( T_CAN_MESSAGE *Elem )
unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned char param )
{
    unsigned char brightness;
    unsigned char ret_value=ret_OK;
    
    if( LightId > MAX_LIGHT_NUM )
    {
        return ret_NOK;
    }
    
    if( (Light_state[LightId].type & LIGHT_TYPE_ACTIVE) == 0 ) // check if output is inhibited
    {
        if( Order != LIGHT_RELEASE_OUTPUT)
        {
            return ret_OK;
        }
    }
    
    switch( Order )
    {
        case LIGHT_OFF :
            if( Light_state[LightId].state > 0)
            {
                // Store the current state to be able to reuse it on the next ON order
                Light_state[LightId].brightness_last = Light_state[LightId].state;
            }
            // Reset the timer and set the state to OFF:
            Light_state[LightId].timer_val = 0;
            Light_state[LightId].state = 0;
        break;
        
        case LIGHT_ON :
            // Reset any timer
            Light_state[LightId].timer_val = 0x0000;

            if( Light_state[LightId].state == 0 )
            {
                // If the light state was OFF before, switch it to on at the max brightness
                Light_state[LightId].state = 0xFF;
            }
            else if( Light_state[LightId].state == 0xFF)
            {
                // Light was already ON at max brightness. Nothing more to do.
            }
            else //( Light_state[OutputNum-1].state > 0 && Light_state[OutputNum-1].state < 0xFF )
            {
                // Light brightness was not at max, so save it for next dimmable use
                Light_state[LightId].brightness_last = Light_state[LightId].state;

                // Set maximum brightness
                Light_state[LightId].state = 0xFF;
            }
        break;

        case LIGHT_REVERSE :
            if ( Light_state[LightId].state )
            {
                // Light is ON
                // Store the current brightness and switch it OFF.
                Light_state[LightId].brightness_last = Light_state[LightId].state ;
                Light_state[LightId].state = 0;
            }
            else
            {
                // Light is OFF
                if( Light_state[LightId].type == LIGHT_TYPE_DIMMABLE)
                {
                    // First check for last brightness
                    if( Light_state[LightId].brightness_last > 0)
                    {
                        // Restore the last known brightness
                        Light_state[LightId].state = Light_state[LightId].brightness_last;
                    }
                    else
                    {
                        // Last brightness is unknown. Put default value and switch ON
                        Light_state[LightId].brightness_last = Light_state[LightId].brightness_default;
                    }
                
                    // Switch it ON, at the last known brightness.
                    Light_state[LightId].state = Light_state[LightId].brightness_last;
                }
                else
                {
                    Light_state[LightId].state = 0xFF; 
                }
            }
        break;

        case LIGHT_ON_LAST_BRIGHTNESS:
            Light_state[LightId].state = Light_state[LightId].brightness_last;
            Light_state[LightId].timer_val = 0;
        break;

        case LIGHT_ON_SPECIFIED_BRIGHTNESS:
            brightness = param;

            if( Light_state[LightId].type & LIGHT_TYPE_DIMMABLE )
            {
                Light_state[LightId].timer_val = 0;
                if( brightness > 0 )
                    Light_state[LightId].state = brightness;
            }
        break;

        case LIGHT_ON_DEFAULT_BRIGHTNESS:
            if( Light_state[LightId].type & LIGHT_TYPE_DIMMABLE )
            {
                if( Light_state[LightId].state > 0 )
                {
                    Light_state[LightId].state = Light_state[LightId].brightness_default;
                    Light_state[LightId].timer_val = 0;
                }
            }
        break;

        case LIGHT_BRIGHTNESS_MORE:
            if( Light_state[LightId].type & LIGHT_TYPE_DIMMABLE )
            {
                if( Light_state[LightId].state > 0 )
                {
                    //Light is already ON. Add brightness if max value is not reached
                    if( Light_state[LightId].state < 10 )
                        Light_state[LightId].state += 1;
                }
                else
                {
                    // Light was OFF, put it on last known brightness:
                    Light_state[LightId].state = Light_state[LightId].brightness_last;
                }
                
                // Reset any timer
                Light_state[LightId].timer_val = 0;
            }
        break;

        case LIGHT_BRIGHTNESS_LESS:
            if( Light_state[LightId].type & LIGHT_TYPE_DIMMABLE )
            {
                if( Light_state[LightId].state > 1 )
                {
                    // Brightness is more than min value. Decrease it.
                    Light_state[LightId].state -= 1;
                }
                else
                {
                    // Light is less than min accepted brightness value. Switch it OFF.
                    Light_state[LightId].state = 0x00;
                }

                // Reset any timer
                Light_state[LightId].timer_val = 0;
            }
        break;

        case LIGHT_ON_TIMER:
            if( Light_state[LightId].state == 0 ) // Light is OFF
            {
                // Light was OFF, set it to max brightness
                Light_state[LightId].state = 0xFF;
            }
            else if( Light_state[LightId].state < 10 )
            {
                // Light was ON but not at max. Save the current brightness for next use
                Light_state[LightId].brightness_last = Light_state[LightId].state;
            }
            else
            {
                // Light was ON at max brightness. Do nothing. Timer will be started just after
            }

            // Start the timer
            Light_state[LightId].timer_val   = Light_state[LightId].timer_default;
        break;

        case LIGHT_ON_TIMER_ADD_30S:
            if( Light_state[LightId].state == 0 )
            {
                // Light is OFF. switch it on at the default timer value.
                Light_state[LightId].timer_val== Light_state[LightId].timer_default;
                Light_state[LightId].state = 0xFF;
            }
            else
            {
                // Light was already ON. Add 15s
                // Let brightness at same value.
                Light_state[LightId].timer_val += 15;
            }
        break;

        case LIGHT_INHIBIT_OUTPUT:
            // type bit7
            // Force Output to 0
            // Switch OFF output
            Light_state[LightId].brightness_last = Light_state[LightId].state;
            Light_state[LightId].state = 0x00;
            Light_state[LightId].timer_val = 0x0000;

            // Disable output:
            Light_state[LightId].type &= ~(LIGHT_TYPE_ACTIVE);
        break;

        case LIGHT_RELEASE_OUTPUT:
            // Reset light state
            Light_state[LightId].state = 0x00;
            Light_state[LightId].timer_val = 0x0000;

            // Enable output:
            Light_state[LightId].type |= LIGHT_TYPE_ACTIVE;
        break;

        default:
            ret_value = ret_NOK;
        break;
    }

	return ret_value;
}


void LightOrderProcess(void)
{
    unsigned char i;
    unsigned char pinnum, pinstate;
    
    for( i=0; i<MAX_LIGHT_NUM; i++)
    {
        if( Light_state[i].curState != Light_state[i].state)
        {
            pinnum = Light_state[i].outPin;
            pinstate = Light_state[i].state;
            //IOsetState( &PinMapping[pinnum], pinstate);
            
            Light_state[i].curState = Light_state[i].state;
            LightSendOutputStatus(i);
        }
    }
}

void LightSendStatus(void)
{
    unsigned char i;
    
    for( i=0; i<MAX_LIGHT_NUM; i++)
    {
        if(Light_state[i].state)
        {
            LightSendOutputStatus(i);
        }
    }
}
        
void LightSendOutputStatus(unsigned char i)
{
    unsigned char pinnum, pinstate;
    unsigned char msg[8];
    
    msg[0]=OWN_CAN_ID;
    msg[1]=i;
    msg[2]=Light_state[i].state;

    CAN_FIFO_add(&CAN_TX_FIFO, CAN_ID_BROADCAST, 3, msg);
}

