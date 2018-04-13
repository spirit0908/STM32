
#include "stm32f10x_map.h"
#include "stm32f10x_gpio.h"



#include "Task.h"
//#include "def.h"
//#include "FIFO.h"
//#include "Order_mgt.h"
//#include "Light.h"
#include "Fifo_Cfg.h"
#include "Task_cfg.h"

extern u8 sens;

//*********************
// Task configuration
//*********************

unsigned char Task_20ms(void);
unsigned char Task_50ms(void);
unsigned char Task_100ms(void);
unsigned char Task_1s(void);
unsigned char Task_10s(void);
unsigned char Task_CanMsgProcess(void);

T_TASK Task_List[] =
{
    { Task_20ms    , TASK_STOPPED, 0, SYNC_TASK, 20   /*ms*/, 0 },
    { Task_50ms    , TASK_STOPPED, 0, SYNC_TASK, 50   /*ms*/, 0 },
    { Task_100ms   , TASK_STOPPED, 0, SYNC_TASK, 100  /*ms*/, 10},
    { Task_1s      , TASK_STOPPED, 0, SYNC_TASK, 1000 /*ms*/, 0 },
	{ Task_10s 	   , TASK_STOPPED, 0, SYNC_TASK, 10000/*ms*/, 0 },
    { Task_CanMsgProcess, TASK_STOPPED, 0, ASYNC_TASK, 0/*ms*/,0}
};
#define TASK_TOTAL_NUM (sizeof(Task_List)/sizeof(T_TASK))

extern unsigned char dim_idx;

//*********************************
// Synchronous tasks implementation
//*********************************

unsigned char Task_20ms(void)
{
    return 0;
}

unsigned char Task_50ms(void)
{
//    CanSendMessage();
    
    return 0;
}

unsigned char cpt_test=0;
unsigned char Task_100ms(void)
{
//    LightOrderProcess();
    
    cpt_test++;
    if( cpt_test >= 10 )
    {
        cpt_test=0;
        // every 1sec
//        LED9 = !LED9;


    }
    
    return 0;
}

unsigned char Task_1s(void)
{
//    LightSendStatus();

	if(sens == 0)
	{
		sens = 1;
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
	else
	{
		sens = 0;
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}

    return 0;
}

u8 RelayPos=0;
unsigned char Task_10s(void)
{
//    LightSendStatus();

	if(RelayPos == 0)
	{
		RelayPos = 1;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}
	else
	{
		RelayPos = 0;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}

    return 0;
}

//**********************************
// Asynchronous tasks implementation
//**********************************
unsigned char Task_CanMsgProcess(void)
{
    unsigned int CanId;
    unsigned char msgLen, msgData[8];
    unsigned char i, NbMsgReceived;
    
    NbMsgReceived = CAN_RX_FIFO.NumElem;
    
    for(i=0; i<NbMsgReceived; i++)
    {
        // Reception of CAN messages
        if( CAN_FIFO_read(&CAN_RX_FIFO, &CanId, &msgLen, msgData) != 0)
        {
//            OrderProcess(CanId, msgLen, msgData);
        }
    }
    
    return 0;
}

