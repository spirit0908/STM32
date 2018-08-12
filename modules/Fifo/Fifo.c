
/************************************************************************
* INCLUDES *
*************************************************************************/
#include "stm32f10x_lib.h"
//#include "stm32f10x_usart.h"
//#include "stm32f10x_can.h"

//#include "stm32f10x_flash.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_map.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"

#include "Fifo.h"

/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/

/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: FIFO_Init                                                  *
 * input: FIFO_table, pPointer to a table that contains all FIFO        *
 * output: none                                                         *
 * return: none                                                         *
 * description: This function initialize all FIFO defined in the table  *
 ************************************************************************/
void FIFO_Init(FIFO_TAB_T *pFifoTab)
{
    // Loop on all FIFO created:
    while(pFifoTab->pFIFO != 0) // #TBD: Whille loop to be tested
    {
        // Initialize Fifo
        (pFifoTab->pFIFO)->msgBuff 		= pFifoTab->pFIFO_Buff; //  FIFO1.msgBuff = FIFO1_Buff;
        (pFifoTab->pFIFO)->size 		= pFifoTab->size;
        (pFifoTab->pFIFO)->WriteIdx 	= 0;
        (pFifoTab->pFIFO)->ReadIdx 		= 0;
        (pFifoTab->pFIFO)->NumElem 		= 0;
        (pFifoTab->pFIFO)->NumMaxElem 	= 0;
        (pFifoTab->pFIFO)->overrun      = 0;
        
        pFifoTab++;
    }
}

/************************************************************************
 * Function: CAN_FIFO_add                                               *
 * input: FIFO: FIFO where message will be added                        *
 *        CAN_Id: Can ID                                                *
 *        msg_len:                                                      *
 *        msg_data                                                      *
 * output: none                                                         *
 * return: none                                                         *
 * description: Add a CAN message in FIFO                               *
 ************************************************************************/
unsigned char CAN_FIFO_add ( T_CAN_FIFO *pFIFO, unsigned int CAN_Id, unsigned char msg_len, unsigned char *msg_data )
{
    unsigned char i, status;
	unsigned char * pWriteIdx;
	T_CAN_MESSAGE * pMsgBuff;

	pWriteIdx = &(pFIFO->WriteIdx);
	
	pMsgBuff = &(pFIFO->msgBuff[*pWriteIdx]);
	
	status=ret_OK;
    
    if( pFIFO->NumElem < pFIFO->size )
	{
        // Store CAN_ID and msg_len
		pMsgBuff->addr = CAN_Id;
		pMsgBuff->length = msg_len;
        
        // Store data
        for( i=0; i<msg_len; i++)
			pMsgBuff->data[i] = msg_data[i];
		
        pFIFO->NumElem++;   // Increment the number of elements
        (*pWriteIdx)++;     // Increment FIFO write index to next position
        
        // Manage overflow:
		if( (*pWriteIdx) >= pFIFO->size )
			*pWriteIdx = 0;

        //Used for debug purpose
        if( pFIFO->NumElem > pFIFO->NumMaxElem)
        {
            pFIFO->NumMaxElem = pFIFO->NumElem; // Record how many elements were used in maximum since startup
        }
	}
	else
	{
		// FIFO overrun
        if( pFIFO->overrun < 0xFF)
        {
            pFIFO->overrun++;
		}
        status = ret_NOK;
	}
    return status;
}

/************************************************************************
 * Function: CAN_FIFO_aread                                             *
 * input: FIFO: FIFO name to read                                       *
 * output:CAN_Id: pointer to store Can ID                               *
 *        msg_len: pointer to store msg length                          *
 *        msg_data: pointer to store data                               *
 * return: OK if element is read, NOK if FIFO is empty                  *
 * description: Add a CAN message in FIFO                               *
 ************************************************************************/
unsigned char CAN_FIFO_read(T_CAN_FIFO *pFIFO, unsigned int *CAN_Id, unsigned char *msg_len, unsigned char msg_data[8] )
{
	unsigned char i;
	T_CAN_MESSAGE pCanMsg;

	u8 tmpCanId, tmpMsgLen;
	
	if( pFIFO->NumElem > 0 )
	{
		pCanMsg = pFIFO->msgBuff[pFIFO->ReadIdx];

        // Get CAN_Id and message length
		tmpCanId = pCanMsg.addr ;
		tmpMsgLen = pCanMsg.length;
        
        // Get on data
		for( i=0; i<tmpMsgLen; i++ )
			msg_data[i] = pFIFO->msgBuff[pFIFO->ReadIdx].data[i];
		
		*CAN_Id = tmpCanId ;
		*msg_len = tmpMsgLen;

        // Remove read element
		pFIFO->NumElem --;
        
        // Increment Read index and manage overrun
		pFIFO->ReadIdx ++;
		if( pFIFO->ReadIdx >= pFIFO->size )
			pFIFO->ReadIdx = 0;
		
		return ret_OK;
	}
	else
    {
        // No element in this buffer
		return ret_NOK;
	}
}

/************************************************************************
 * Function:                                              				*
 * input: FIFO: FIFO name to read                                       *
 * output:																*
 * return: OK if element is read, NOK if FIFO is empty                  *
 * description: Add a CAN message in FIFO                               *
 ************************************************************************/
unsigned char CAN_FIFO_GetNumOfElem(T_CAN_FIFO *pFIFO)
{
	return pFIFO->NumElem;
}



/*******************************************************************************
 * Function Name  : FIFO_add
 * Description    : Add one element in Fifo
 * Input          : pFIFO -> pointer to Fifo
 * 					data  -> data to write
 * Output         : None
 * Return         : status -> ret_OK when element is correctly stored, ret_NOK otherwise
 *******************************************************************************/
unsigned char FIFO_add ( T_FIFO *pFIFO, unsigned char data )
{
    unsigned char status;
	unsigned char * pWriteIdx;
	unsigned char * pDataElem;

	pWriteIdx = &(pFIFO->WriteIdx);

	pDataElem = &(pFIFO->dataElem[*pWriteIdx]);

	status=ret_OK;

    if( pFIFO->NumElem < pFIFO->size )
	{
        // record data
    	*pDataElem = data;

        pFIFO->NumElem++;   // Increment the number of elements
        (*pWriteIdx)++;     // Increment FIFO write index to next position

        // Manage overflow:
		if( (*pWriteIdx) >= pFIFO->size )
			*pWriteIdx = 0;

        //Used for debug purpose
        if( pFIFO->NumElem > pFIFO->NumMaxElem)
        {
            pFIFO->NumMaxElem = pFIFO->NumElem; // Record how many elements were used in maximum since startup
        }
	}
	else
	{
		// FIFO overrun
        if( pFIFO->overrun < 0xFF)
        {
            pFIFO->overrun++;
		}
        status = ret_NOK;
	}
    return status;
}

/*******************************************************************************
 * Function Name  : FIFO_add
 * Description    : Read first entry available in a Fifo
 * Input          : pFIFO -> pointer to Fifo
 * Output         : data  -> data to return
 * Return         : status -> ret_OK when element is correctly read, ret_NOK otherwise
 *******************************************************************************/
unsigned char FIFO_read(T_FIFO *pFIFO, unsigned char *data )
{
	unsigned char i;

	if( pFIFO->NumElem > 0 )
	{
        // Get data
		*data = pFIFO->dataElem[pFIFO->ReadIdx];

		// Remove read element
		pFIFO->NumElem --;

        // Increment Read index and manage overrun
		pFIFO->ReadIdx ++;
		if( pFIFO->ReadIdx >= pFIFO->size )
			pFIFO->ReadIdx = 0;

		return ret_OK;
	}
	else
    {
        // No element in this buffer
		return ret_NOK;
	}
}



