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
#define MAX_HEATING_NUM	1

/************************************************************************
* DEFINES *
************************************************************************/
#define DELTA_TEMP_ECO 2*2

/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct
{
	unsigned char mode;
	unsigned char temperature;
	unsigned char temperature_default;
	unsigned char temperature_confort;
}T_HeatingState;


/************************************************************************
* STRUCTURES *
************************************************************************/
typedef enum
{
	HEATING_MODE_OFF,
	HEATING_MODE_NORMAL,
	HEATING_MODE_ECO,
	HEATING_MODE_CONFORT,
	HEATING_MODE_FROST,
	HEATING_MODE_ERROR,
	HEATING_MODE_INIT,
	HEATING_MODE_INHIBIT,
	HEATING_MODE_ACTIVATE
}T_Heating_Mode;


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void Heating_Init(void);
unsigned char HeatingOrderTmt( unsigned char DeviceId, unsigned char Order, unsigned char *param);


#endif /* HEATING_H_ */
