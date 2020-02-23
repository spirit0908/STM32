/************************************************************************
 * File Name          : templace_source.c
 * Author             : author
 * Date               : 23/02/2020
 * Description        : source template file
 ***********************************************************************/

/************************************************************************
* INCLUDES *
************************************************************************/
#include "Std_Types.h"
#include "Heating.h"
/************************************************************************
* DEFINES *
************************************************************************/

/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
T_HeatingState HeatingState;

/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: Heating_Init                                               *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Initialization function of Heating module               *
 ************************************************************************/
void Heating_Init(void)
{
    unsigned char i;

    for(i=0u; i<MAX_HEATING_NUM; i++)
    {
    	HeatingState.mode 					= HEATING_MODE_OFF;
    	HeatingState.temperature_default 	= 20*2;
    	HeatingState.temperature_confort 	= 21*2;
    	HeatingState.temperature 			= HeatingState.temperature_default;

    }
}

/************************************************************************
 * Function: HeatingOrderTmt                                            *
 * input: DeviceId - Device identifier                                  *
 *        Order - Order to execute                                      *
 *        param - pointer to parameters                                 *
 * return: none                                                         *
 * description: Treatment of the received order                         *
 ************************************************************************/
unsigned char HeatingOrderTmt( unsigned char DeviceId, unsigned char Order, unsigned char *param)
{
	unsigned char ret_value;

    switch( Order )
    {
        case HEATING_MODE_OFF:
            HeatingState.mode = HEATING_MODE_OFF;
        break;
        
        case HEATING_MODE_NORMAL:
        	HeatingState.mode = HEATING_MODE_NORMAL;
        	HeatingState.temperature = HeatingState.temperature_default;
        break;

        case HEATING_MODE_ECO:
        	HeatingState.mode = HEATING_MODE_ECO;
        	HeatingState.temperature = HeatingState.temperature_confort - DELTA_TEMP_ECO;
        break;

        case HEATING_MODE_CONFORT:
        	HeatingState.mode = HEATING_MODE_CONFORT;
        	HeatingState.temperature = HeatingState.temperature_confort;
        break;

        case HEATING_MODE_FROST:
        	HeatingState.mode = HEATING_MODE_FROST;
        break;

        case HEATING_MODE_INHIBIT:
        	HeatingState.mode = HEATING_MODE_OFF;
        break;

        case HEATING_MODE_ACTIVATE:
        	HeatingState.mode = HEATING_MODE_OFF;
        break;

        default:
        	ret_value = ret_NOK;
        break;
    }

    return ret_value;
}
