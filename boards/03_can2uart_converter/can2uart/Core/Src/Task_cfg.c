
//#include "stm32f10x_lib.h"
//#include "stm32f10x_map.h"
//#include "stm32f10x_gpio.h"
//#include "teleinfo.h"
//#include "PushButton.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#include "Task.h"
//#include "def.h"
//#include "FIFO.h"
//#include "Order_mgt.h"
//#include "Light.h"
//#include "Fifo_Cfg.h"
#include "Task_cfg.h"
//#include "Light.h"
//#include "LedStrip.h"
//#include "serial.h"
//#include "Order_mgt.h"

//extern u8 sens;


extern CAN_HandleTypeDef hcan;

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
    return 0;
}

unsigned char Task_50ms(void)
{
    return 0;
}


unsigned char cpt_test=0;
unsigned char Task_100ms(void)
{
    cpt_test++;
    if( cpt_test >= 10 )
    {
        cpt_test=0;
    }
    

    return 0;
}


unsigned char Task_1s(void)
{
    unsigned char i;

    {
        uint32_t TxMailbox;
        uint8_t TxData[8];
        CAN_TxHeaderTypeDef TxMessage;


        TxData[0] = 0x12;
        TxData[1] = 0x00;

        TxMessage.DLC = 2;
        TxMessage.IDE = CAN_ID_STD;
        TxMessage.RTR = CAN_RTR_DATA;
        TxMessage.StdId = 0x100;
        TxMessage.TransmitGlobalTime = DISABLE;

        HAL_CAN_AddTxMessage(&hcan, &TxMessage, TxData, &TxMailbox);
    }

    return 0;
}

unsigned char RelayPos=0;

unsigned char Task_10s(void)
{
    if(RelayPos == 0)
    {
        RelayPos = 1;
    }
    else
    {
        RelayPos = 0;
    }

    return 0;
}

//**********************************
// Asynchronous tasks implementation
//**********************************
unsigned char Task_CanMsgProcess(void)
{
    return 0;
}

