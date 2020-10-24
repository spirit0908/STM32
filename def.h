/************************************************************************
 * File Name          : def.h
 * Author             : author
 * Date               : 23/02/2020
 * Description        : Contains defines related to the hardware
 ***********************************************************************/

#ifndef DEF_H
#define DEF_H

/************************************************************************
* INCLUDES *
************************************************************************/


/************************************************************************
* DEFINES *
************************************************************************/
/* Return values */
#define RET_OK              0
#define RET_NOT_OK          1

/* Address of the board */
#define OWN_DEVICE_ID       0x48
#define OWN_CAN_ID          OWN_DEVICE_ID
#define CAN_ID_BROADCAST    OWN_DEVICE_ID

/* Version of the project, for compatibility issues with the protocol */
#define PROJECT_VERSION     0


/************************************************************************
* STRUCTURES *
************************************************************************/


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/

#endif /* DEF_H */
