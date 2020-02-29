/************************************************************************
 * File Name          : templace_header.h
 * Author             : author
 * Date               : 08/06/2017
 * Description        : header template file
 ***********************************************************************/

#ifndef ORDER_MGT_H
#define ORDER_MGT_H

/************************************************************************
* INCLUDES *
************************************************************************/


/************************************************************************
* DEFINES *
************************************************************************/
#define ORDER_BROADCAST     0x00
#define ORDER_LIGHT         0x10
#define ORDER_HEATING       0x20
#define ORDER_SHUTTER       0x30
#define ORDER_MEASUREMENT   0x40

#define TYPE_LIGHT          0x10


/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct{
    unsigned char ElemId;
    unsigned char type;
    unsigned int  Addr;
    unsigned char FctId;
    unsigned char (*pRxIndication)();
}T_FctGrp;


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void OrderProcess(unsigned int CanId, unsigned char msgData[8], unsigned char msgLen);
void updateIndicStatus(unsigned char Idx);
unsigned char CanSendMessage(void);

#endif  /* ORDER_MGT_H */

