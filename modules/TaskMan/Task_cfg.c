
#include "stm32f10x_lib.h"
#include "stm32f10x_map.h"
#include "stm32f10x_gpio.h"
#include "teleinfo.h"
#include "PushButton.h"

#include "Task.h"
//#include "def.h"
//#include "FIFO.h"
//#include "Order_mgt.h"
//#include "Light.h"
#include "Fifo_Cfg.h"
#include "Task_cfg.h"
#include "Light.h"
#include "LedStrip.h"

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
    { Task_10s     , TASK_STOPPED, 0, SYNC_TASK, 10000/*ms*/, 0 },
    { Task_CanMsgProcess, TASK_STOPPED, 0, ASYNC_TASK, 0/*ms*/,0}
};
#define TASK_TOTAL_NUM (sizeof(Task_List)/sizeof(T_TASK))
#define PERIOD 1000

extern unsigned char dim_idx;

extern int TIM_Pulse_R;
extern int TIM_Pulse_G;
extern int TIM_Pulse_B;

//*********************************
// Synchronous tasks implementation
//*********************************

unsigned char Task_20ms(void)
{
	LedStrip_Mgt();

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
    unsigned char PBState, i;
    
    cpt_test++;
    if( cpt_test >= 10 )
    {
        cpt_test=0;
        // every 1sec
//        LED9 = !LED9;
    }
    
    PushButton_Mgt();

    SerialOrder_Mgt();

    //LedStrip_Mgt();
/*
    if(TIM3->CCR1 < TIM_Pulse_R)
    {
    	TIM3->CCR1 +=1;
    }*/

    //LedStrip_Mgt();

    return 0;
}

unsigned char order=0;
unsigned char Task_1s(void)
{
	unsigned char i;

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
/*
    TIM_Pulse_R++;
    if (TIM_Pulse_R > PERIOD)
        TIM_Pulse_R = 0;

    TIM_Pulse_G +=2;
    if (TIM_Pulse_G > PERIOD)
        TIM_Pulse_G = 0;

    TIM_Pulse_B +=4;
    if (TIM_Pulse_B > PERIOD)
        TIM_Pulse_B = 0;

    TIM3->CCR1 = TIM_Pulse_R;
    TIM3->CCR2 = TIM_Pulse_G;
    TIM3->CCR3 = TIM_Pulse_B;*/


    if(order)
    {
    	order = 0;
    }
    else
    {
    	order = 1;
    }
    LightOrderTmt( 0, 0x10+order, 0 );
    LightOrderTmt( 1, 0x12, 0 );

    for(i=0; i<2; i++)
    {
    	if( LightState[i].state )
    	{
    		GPIO_SetBits(LightConfig[i].GPIO_Port, LightConfig[i].GPIO_Pin);
    	}
    	else
    	{
			GPIO_ResetBits(LightConfig[i].GPIO_Port, LightConfig[i].GPIO_Pin);
		}
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

