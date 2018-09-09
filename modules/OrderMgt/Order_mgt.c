
//#include "hard.h"
#include "Order_mgt.h"
#include "def.h"
#include "Light.h"
#include "Fifo.h"

#include "stm32f10x_can.h"

T_FctGrp fct_group[] =
{
    /* ElemId, type , Addr, FctId, pRxIndication */
    { 0u, TYPE_LIGHT, 0x123, 0u, LightOrderTmt }, // FCT_GROUP 0 - SORTIE 0 - 
    { 1u, TYPE_LIGHT, 0x123, 1u, LightOrderTmt }, // SORTIE 1
    { 2u, TYPE_LIGHT, 0x123, 2u, LightOrderTmt }, // SORTIE 2
    { 3u, TYPE_LIGHT, 0x123, 3u, LightOrderTmt }, // SORTIE 3
    { 4u, TYPE_LIGHT, 0x123, 4u, LightOrderTmt }, // SORTIE 4
    { 5u, TYPE_LIGHT, 0x123, 5u, LightOrderTmt }, // SORTIE 5
    { 6u, TYPE_LIGHT, 0x123, 6u, LightOrderTmt }, // SORTIE 6
    { 7u, TYPE_LIGHT, 0x123, 7u, LightOrderTmt }  // SORTIE 7
};
#define fct_group_size ( sizeof(fct_group)/sizeof(T_FctGrp) ) //(sizeof(fct_group) / sizeof(T_FctGrp))

T_FctGrp fct_group2[] =
{
    /* ElemId   , type      , pRxIndication */
    { Light_ID_0, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_1, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_2, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_3, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_4, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_5, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_6, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_7, TYPE_LIGHT, LightOrderTmt }
};

//void OrderProcess(unsigned int CanId, unsigned char msgLenm, unsigned char msgData[8])
void OrderProcess(unsigned int Order, unsigned char msgLenm, unsigned char msgData[8])
{
    unsigned char deviceModule;
    unsigned char LightId, param;
    unsigned char i;
    unsigned int temp;
    deviceModule = (msgData[0] & 0xF0u);
    
        //Loop on all functionnal groups
        for(i=0; i<fct_group_size; i++)
        {
            
        }
        
        switch(deviceModule)
        {
            case ORDER_BROADCAST:
                // this message is a broadcast

                // check if we are concerned by the can id
            break;

            case ORDER_LIGHT:
                Order   = msgData[0];
                LightId = msgData[1];
                param   = msgData[2];

                LightOrderTmt(LightId, Order, param);
            break;

            case ORDER_HEATING:
                //HeatingOrderTmt();
            break;

            case ORDER_SHUTTER:
                //ShutterOrderTmt();
            break;
        }


    
}



void updateIndicStatus(unsigned char Idx)
{
}



void CanSendMessage(void)
{
    unsigned char NbMsgToSend;
    unsigned char retVal, i;
    CanTxMsg TxMessage;

    T_CAN_MESSAGE tmpCanMsg;

    // Send CAN messages    
    NbMsgToSend = CAN_TX_FIFO.NumElem;
    
    for(i=0; i<NbMsgToSend; i++)
    {
        if( CAN_FIFO_read(&CAN_TX_FIFO, &tmpCanMsg.addr, &tmpCanMsg.length, tmpCanMsg.data) != 0)
        {
            TxMessage.StdId = tmpCanMsg.addr;
            TxMessage.DLC = tmpCanMsg.length;
            for(i=0; i<TxMessage.DLC; i++)
            {
                TxMessage.Data[i] = tmpCanMsg.data[i];
            }

            if( CAN_Transmit(&TxMessage) != CAN_NO_MB)
            {
                //return TRUE;
                retVal = ret_OK;
            }
            else
            {
                // no free slot, insert the msg back
                CAN_FIFO_add(&CAN_TX_FIFO, TxMessage.StdId, TxMessage.DLC, TxMessage.Data);
                retVal = ret_NOK;
            }
        }
    }
}


