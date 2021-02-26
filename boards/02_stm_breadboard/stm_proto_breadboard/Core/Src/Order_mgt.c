/************************************************************************
 * File Name          : templace_source.c
 * Author             : author
 * Date               : 08/06/2017
 * Description        : source template file
 ***********************************************************************/


/************************************************************************
* INCLUDES *
************************************************************************/
#include "Order_mgt.h"
//#include "def.h"
#include "Light.h"
//#include "Heating.h"
//#include "Fifo.h"
#include "Std_Types.h"
//#include "stm32f10x_can.h"


/************************************************************************
* DEFINES *
************************************************************************/
#define fct_group_size ( sizeof(fct_group)/sizeof(T_FctGrp) ) //(sizeof(fct_group) / sizeof(T_FctGrp))

// #define GETVERSION(data)        (data[0])
#define COMMAND_TYPE(data)      (data[0]&0xF0)
#define COMMAND_ORDER(data)     (data[0])
#define COMMAND_ID(data)        (data[1])
#define COMMAND_PARAM_PTR(data) (&data[2])

#define FRAME_TYPE_COMMAND      1
#define FRAME_TYPE_CONFIG       2
#define FRAME_TYPE_STATUS       3


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
T_FctGrp fct_group[] =
{
    /* ElemId, type , Addr, FctId, pRxIndication */
    { 0u, TYPE_LIGHT, 0x123, 0u, &LightOrderTmt }, // FCT_GROUP 0 - SORTIE 0 - 
    { 1u, TYPE_LIGHT, 0x123, 1u, &LightOrderTmt }, // SORTIE 1
    { 2u, TYPE_LIGHT, 0x123, 2u, &LightOrderTmt }, // SORTIE 2
    { 3u, TYPE_LIGHT, 0x123, 3u, &LightOrderTmt }, // SORTIE 3
    { 4u, TYPE_LIGHT, 0x123, 4u, &LightOrderTmt }, // SORTIE 4
    { 5u, TYPE_LIGHT, 0x123, 5u, &LightOrderTmt }, // SORTIE 5
    { 6u, TYPE_LIGHT, 0x123, 6u, &LightOrderTmt }, // SORTIE 6
    { 7u, TYPE_LIGHT, 0x123, 7u, &LightOrderTmt }  // SORTIE 7
};

T_FctGrp fct_group2[] =
{
    /* ElemId   , type      , pRxIndication */
    // { Light_ID_0, TYPE_LIGHT, LightOrderTmt },
    // { Light_ID_1, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_2, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_3, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_4, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_5, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_6, TYPE_LIGHT, LightOrderTmt },
//    { Light_ID_7, TYPE_LIGHT, LightOrderTmt }
};


/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: OrderProcess                                               *
 * input: CanId                                                         *
          msgData                                                       *
          msgLen                                                        *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void OrderProcess(unsigned int CanId, unsigned char msgData[8], unsigned char msgLen)
{
    unsigned char DeviceId, Order;
    unsigned char *paramPtr;

    if( CanId == OWN_CAN_ID )
    {
        switch(COMMAND_TYPE(msgData))
        {
            case ORDER_BROADCAST:
                // this message is a broadcast
                // check if we are concerned by the can id
            break;

            case ORDER_LIGHT:
                Order    = COMMAND_ORDER(msgData);
                DeviceId = COMMAND_ID(msgData);
                paramPtr = COMMAND_PARAM_PTR(msgData);

                LightOrderTmt(DeviceId, Order, paramPtr);
            break;

            case ORDER_HEATING:
                Order    = COMMAND_ORDER(msgData);
                DeviceId = COMMAND_ID(msgData);
                paramPtr = COMMAND_PARAM_PTR(msgData);
                //HeatingOrderTmt(DeviceId, Order, paramPtr);
            break;

            case ORDER_SHUTTER:
                //ShutterOrderTmt(DeviceId, Order, &param);
            break;

            case ORDER_MEASUREMENT:
                //MesurementOrderTmt(DeviceId, Order, &param);
            break;

        }
    }
}

/************************************************************************
 * Function: updateIndicStatus                                          *
 * input: Idx                                                           *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void updateIndicStatus(unsigned char Idx)
{

}

/************************************************************************
 * Function: CanSendMessage                                             *
 * input: none                                                          *
 * output: none                                                         *
 * return:                                                              *
 * description:                                                         *
 ***********************************************************************/
unsigned char CanSendMessage(void)
{
    unsigned char NbMsgToSend;
    unsigned char retVal, i;
/*    CanTxMsg TxMessage;

    T_CAN_MESSAGE tmpCanMsg;

    // Send CAN messages    
    NbMsgToSend = CAN_TX_FIFO.NumElem;
    //TODO: use: unsigned char CAN_FIFO_GetNumOfElem(T_CAN_FIFO *pFIFO)
    
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
*/
    return retVal;
}


/************************************************************************
 * Function: CanSendMessage                                             *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description:                                                         *
 ***********************************************************************/
void SerialOrder_Mgt(void)
{
    USART_SendData(USART2, 'S');
    Delay(0xAFFFF);

    //OrderProcess(unsigned int Order, unsigned char msgLenm, unsigned char msgData[8])
}
