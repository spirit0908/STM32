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
T_HeatingConfig HeatingState[HEATING_MAX_DEVICES];

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

  for(i=0u; i<HEATING_MAX_DEVICES; i++)
  {
  	HeatingState[i].state 				= HEATING_STATE_OFF;
  	HeatingState[i].mode 				= HEATING_MODE_OFF;

    HeatingState[i].threshold           = 1;
   	HeatingState[i].temperature_default	= 20*2;
   	HeatingState[i].temperature_confort = 21*2;
   	HeatingState[i].temperature 		= 0;
    HeatingState[i].consigne            = HeatingState[i].temperature_default;;
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
  unsigned char retVal = ret_NOK;

  T_HeatingConfig HeatingStatePtr = HeatingState[DeviceId];

  switch( Order )
  {
    case HEATING_MODE_NORMAL:
      HeatingStatePtr.temperature = HeatingStatePtr.temperature_default;
      retVal = ret_OK;
    break;

    case HEATING_MODE_ECO:
      HeatingStatePtr.temperature = HeatingStatePtr.temperature_confort - DELTA_TEMP_ECO;
      retVal = ret_OK;
    break;

    case HEATING_MODE_CONFORT:
      HeatingStatePtr.temperature = HeatingStatePtr.temperature_confort;
      retVal = ret_OK;
    break;

    case HEATING_MODE_OFF:
    case HEATING_MODE_FROST:
    case HEATING_MODE_INHIBIT:
    case HEATING_MODE_ACTIVATE:
      retVal = ret_OK;
    break;

    default:
      retVal = ret_NOK;
    break;
  }

  if( retVal == ret_OK)
  {
    HeatingStatePtr.mode = Order;
  }

  return retVal;
}

/************************************************************************
 * Function: unsigned char Heating_mainfunction                         *
 * input: none                                                          *
 * return: none                                                         *
 * description: Main function                                           *
 ************************************************************************/
unsigned char Heating_mainfunction(void)
{
  unsigned char ret_value;
  unsigned char i;
  T_HeatingConfig * HeatingStatePtr;

  for(i=0u; i<HEATING_MAX_DEVICES; i++)
  {
    HeatingStatePtr = &HeatingState[i];

    switch( HeatingStatePtr->state )
    {
      case HEATING_STATE_OFF:
      break;
      
      case HEATING_STATE_WAIT:
        if(HeatingStatePtr->temperature <= (HeatingStatePtr->consigne - HeatingStatePtr->threshold) )
        {
          HeatingStatePtr->state = HEATING_STATE_HEAT;
        }
      break;

      case HEATING_STATE_HEAT:
        if(HeatingStatePtr->temperature >= (HeatingStatePtr->consigne + HeatingStatePtr->threshold) )
        {
          HeatingStatePtr->state = HEATING_STATE_WAIT;
        }
        
      break;

      default:
        HeatingStatePtr->state = HEATING_STATE_OFF;
        ret_value = ret_NOK;
      break;
    }
  }
  return ret_value;
}


