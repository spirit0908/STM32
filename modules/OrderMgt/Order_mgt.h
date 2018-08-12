/* 
 * File:   Order_mgt.h
 * Author: spirit
 *
 * Created on June 8, 2017, 10:26 PM
 */

#ifndef ORDER_MGT_H
#define	ORDER_MGT_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define ORDER_BROADCAST 0x00
#define ORDER_LIGHT		0x10
#define ORDER_HEATING	0x20
#define ORDER_SHUTTER	0x30

#define TYPE_LIGHT		0x10


typedef struct{
    unsigned char ElemId;
    unsigned char type;
    unsigned int  Addr;
    unsigned char FctId;
    unsigned char (*pRxIndication)();
}T_FctGrp;


void OrderProcess(unsigned int Order, unsigned char msgLenm, unsigned char msgData[8]);
void updateIndicStatus(unsigned char Idx);
void CanSendMessage(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ORDER_MGT_H */

