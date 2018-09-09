
#ifndef FIFO_H
#define FIFO_H

#include "Std_Types.h"
//#include "Fifo_cfg.h"
/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct          // Creation d'une structure CAN pour la FIFOCAN
{
    // For each CAN message :
    unsigned int addr;      // address
    unsigned char length;   // data length
    unsigned char data[8];  // data (max 8 bytes)
} T_CAN_MESSAGE ;


typedef struct
{
    // FIFO struct for CAN messages
    T_CAN_MESSAGE *msgBuff;     // Message buffer
    unsigned char size;         // FIFO length
    unsigned char WriteIdx;     // Next position to write an element
    unsigned char ReadIdx;      // Next Element to read
    unsigned char NumElem;      // Total of elements currently in the FIFO
    unsigned char NumMaxElem;   // maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_CAN_FIFO;

typedef struct
{
    // This is a FIFO struct
    unsigned char *dataElem;        // Data buffer
    unsigned char size;         // FIFO length
    unsigned char WriteIdx;     // Next position to write an element
    unsigned char ReadIdx;      // Next Element to read
    unsigned char NumElem;      // Total of elements currently in the FIFO
    unsigned char NumMaxElem;   // maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_FIFO;

typedef struct
{
    T_CAN_FIFO *pFIFO;
    T_CAN_MESSAGE *pFIFO_Buff;
    unsigned char size;
} FIFO_TAB_T ;

extern T_CAN_FIFO CAN_RX_FIFO;
extern T_CAN_MESSAGE CAN_RX_FIFO_Buff[];

extern T_CAN_FIFO CAN_TX_FIFO;
extern T_CAN_MESSAGE CAN_TX_FIFO_Buff[];

extern T_CAN_FIFO USART_RX_FIFO;
extern unsigned char USART_RX_FIFO_Buff[];

extern T_FIFO TELEINFO_FIFO;
extern unsigned char TELEINFO_FIFO_Buff[];


extern FIFO_TAB_T FIFO_table[];

void FIFO_Init(FIFO_TAB_T *pFifoTab);
unsigned char CAN_FIFO_add ( T_CAN_FIFO *pFIFO, unsigned int CAN_Id, unsigned char msg_len, unsigned char *msg_data);
unsigned char CAN_FIFO_read(T_CAN_FIFO *pFIFO, unsigned int *CAN_Id, unsigned char *msg_len, unsigned char *msg_data);

unsigned char FIFO_add ( T_FIFO *pFIFO, unsigned char data );
unsigned char FIFO_read(T_FIFO *pFIFO, unsigned char *data );

#endif
