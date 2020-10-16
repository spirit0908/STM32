/************************************************************************
 * File Name          : Heating.h
 * Author             : author
 * Date               : 23/02/2020
 * Description        : header file for heating functions
 ***********************************************************************/
#ifndef HEATING_H_
#define HEATING_H_

/************************************************************************
* INCLUDES *
************************************************************************/

/************************************************************************
* DEFINES *
************************************************************************/
#define HEATING_MAX_DEVICES         2
#define DELTA_TEMP_ECO            2*2
#define DELTA_TEMP_CONFORT        2*2

/************************************************************************
* STRUCTURES *
************************************************************************/
typedef enum
{
	HEATING_MODE_OFF = 0,
	HEATING_MODE_NORMAL,
	HEATING_MODE_ECO,
	HEATING_MODE_CONFORT,
	HEATING_MODE_FROST,
//	HEATING_MODE_ERROR,
//	HEATING_MODE_INIT,
	HEATING_MODE_INHIBIT,
	HEATING_MODE_ACTIVATE
}T_Heating_Mode;

typedef enum
{
	HEATING_STATE_OFF,
	HEATING_STATE_WAIT,
	HEATING_STATE_HEAT,
	HEATING_STATE_,
}T_HeatingSM_State;

typedef struct
{
	T_Heating_Mode mode; 
	T_HeatingSM_State state;
	unsigned char consigne;
	unsigned char threshold;
	unsigned char temperature;
	unsigned char temperature_default;
	unsigned char temperature_confort;
}T_HeatingConfig;

/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern T_HeatingConfig HeatingState[HEATING_MAX_DEVICES];

/************************************************************************
* FUNCTIONS PROTOTYPES *
************************************************************************/
void Heating_Init(void);
unsigned char HeatingOrderTmt( unsigned char DeviceId, unsigned char Order, unsigned char *param);
unsigned char Heating_mainfunction(void);

#endif /* HEATING_H_ */
