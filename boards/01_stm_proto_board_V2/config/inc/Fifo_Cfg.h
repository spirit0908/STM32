/************************************************************************
 * File Name          : Fifo_cfg.h
 * Author             :
 * Date               : 29/02/2020
 * Description        :
 ***********************************************************************/

#ifndef FIFO_CFG_H
#define FIFO_CFG_H


/************************************************************************
* INCLUDES *
************************************************************************/
#include "Fifo.h"


/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* STRUCTURES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern T_CAN_FIFO CAN_RX_FIFO;
#define CAN_RX_FIFO_BUFF_LENGTH    20
extern T_CAN_MESSAGE CAN_RX_FIFO_Buff[CAN_RX_FIFO_BUFF_LENGTH]; // Create the buffer

extern T_CAN_FIFO CAN_TX_FIFO;
#define CAN_TX_FIFO_LENGTH     5
extern T_CAN_MESSAGE CAN_TX_FIFO_Buff[CAN_TX_FIFO_LENGTH];

extern T_FIFO SERIAL_TX_FIFO;
#define SERIAL_TX_FIFO_LENGTH     50
extern unsigned char SERIAL_TX_FIFO_Buff[SERIAL_TX_FIFO_LENGTH];

//extern T_FIFO TELEINFO_FIFO;
//#define TELEINFO_FIFO_LENGTH     250
//extern unsigned char TELEINFO_FIFO_Buff[TELEINFO_FIFO_LENGTH];


extern FIFO_TAB_T FIFO_table[];

/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/


#endif /* FIFO_CFG_H */
