/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
 * File Name          : main.c
 * Author             : MCD Application Team
 * Version            : V1.0
 * Date               : 10/08/2007
 * Description        : Main program body
 ********************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_usart.h"
#include "picture.h"
#include "n3310.h"
#include "stm32f10x_can.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_type.h"
#include "stm32f10x_tim.h"

#include "teleinfo.h"
#include "Task.h"
#include "Task_cfg.h"
#include "Fifo_Cfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CAN_RX_PIN        GPIO_Pin_11
#define CAN_TX_PIN        GPIO_Pin_12
#define CAN_RS_PIN        GPIO_Pin_5
//#define CAN_GPIO_PORT     GPIOB


#define CAN_BAUDRATE_10KBPS     10
#define CAN_BAUDRATE_20KBPS     20
#define CAN_BAUDRATE_50KBPS     50
#define CAN_BAUDRATE_100KBPS    100
#define CAN_BAUDRATE_125KBPS    125
#define CAN_BAUDRATE_250KBPS    250
#define CAN_BAUDRATE_500KBPS    500
#define CAN_BAUDRATE_1MPBS      1000

#define CAN_BAUDRATE CAN_BAUDRATE_125KBPS

#define PERIOD 1000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

CAN_FilterInitTypeDef CAN_FilterInitStructure;

int TIM_Pulse_R = 0;
int TIM_Pulse_G = 0;
int TIM_Pulse_B = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);

void GPIOInit(void);
void SerialInit(void);
void CanInit(void);
void ITInit(void);

//void CAN_Config(void);

/* Private functions ---------------------------------------------------------*/

CanTxMsg CanTxMessage;

/*******************************************************************************
 * Function Name  : main
 * Description    : Main program.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int main(void)
{
#ifdef DEBUG
    debug();
#endif
//    u16 R.cvData=0;
    CanTxMsg TxMessage;

    unsigned int i;

    /* SYSTEM DRIVER INIT */
    /* Configure the system clocks */
    RCC_Configuration();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* NVIC Configuration */
    NVIC_Configuration();

    /* Gpio */
    GPIOInit();
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /* COM DRIVER INIT */
    /* Serial Port */
    SerialInit();

    /* CAN Bus */
    CanInit();

    /* Timer */
    TimerInit();

    /* Interrupt */
    ITInit();

    /* PWM */
    PWMInit();

    /* CONFIG INIT */

    /* Send START message over USART bus */
    USART_SendData(USART2, 'S');
    Delay(0xAFFFF);
    USART_SendData(USART2, 'T');
    Delay(0xAFFFF);
    USART_SendData(USART2, 'A');
    Delay(0xAFFFF);
    USART_SendData(USART2, 'R');
    Delay(0xAFFFF);
    USART_SendData(USART2, 'T');
    Delay(0xAFFFF);


    GPIO_ResetBits(GPIOB, CAN_RS_PIN);

    TxMessage.StdId = 0x444;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 1;
    TxMessage.Data[0] = 0xAA;
    CAN_Transmit(&TxMessage);


    /* MODULE INIT */

    /* Teleinfo initialization */
    teleinfo_Init();
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    /* FIFO table initialization */
    FIFO_Init(&FIFO_table);

    /* LCD Initialization */
    LcdInit();
    LcdClear();

    LcdMenu_Init();
    LcdMenu_Display();

    while(1)
    {
        TaskManager();
    }
}

/*******************************************************************************
 * Function Name  : GPIOInit
 * Description    : Initializes GPIOs.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void TimerInit(void)
{
    TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Timer 4 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // Enable clock peripheral TIM4

    TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER_InitStructure.TIM_Prescaler = 7200;
    TIMER_InitStructure.TIM_Period = 50;       //5ms delay / 1sec delay: F=72000000/7200/10000 = 1sec
    TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

void GPIOInit(void)
{
    /* Enable GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


    /* Configure PB.0 as Alternate Function push-pull - TIM3_CH3*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure PA.6 as Alternate Function push-pull - TIM3_CH1*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA.7 as Alternate Function push-pull -  TIM3_CH2*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PC.13 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    /* USART1 TX */
    /* Configure PB.6 as Alternate Function Push-Pull Output - Serial TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART1 RX */
    /* Configure PB.7 as Alternate Function Floating Input - Serial RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART2 TX */
    /* Configure PA.2 as Alternate Function Push-Pull Output - Serial TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART2 RX */
    /* Configure PA.3 as Alternate Function Floating Input - Serial RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART3 TX */
    /* Configure PB.10 as Alternate Function Push-Pull Output - Serial TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART3 RX */
    /* Configure PB.11 as Alternate Function Floating Input - Serial RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* CAN1 TX */
    /* Configure PA.12 as Alternate Function Push-Pull Output - CAN TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //CAN_TX_PIN
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* CAN RX */
    /* Configure PA.11 as Alternate Function Floating Input - CAN RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  //CAN_RX_PIN
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* CAN RS */
    /* Configure PB.5 as Push-Pull Output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    /* IO */

    /* Configure PA.0 as Input - PushButton UP */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*******************************************************************************
 * Function Name  : SerialInit
 * Description    : Initializes the serial link.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SerialInit(void)
{
    USART_InitTypeDef USART_InitStruct;

    /* *** USART1 *** */
    /* Enable USART1 clock */
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);

    /* Enable USART  */
    USART_StructInit(&USART_InitStruct);
    USART_Cmd(USART1, DISABLE);
    USART_Init(USART1, &USART_InitStruct);

    /* Enable IT on USART handler */
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);


    /* *** USART2 *** */
    /* Enable USART2 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Enable USART  */
    USART_StructInit(&USART_InitStruct);
    USART_Cmd(USART2, ENABLE);
    USART_Init(USART2, &USART_InitStruct);

    /* Enable IT on USART handler */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);


    /* *** USART3 *** */
    /* Enable USART3 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* Configure UART for EDF Teleinfo */
    USART_InitStruct.USART_BaudRate     = 0x04B0; /* 1200 Baud */
    USART_InitStruct.USART_WordLength   = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits     = USART_StopBits_1;
    USART_InitStruct.USART_Parity       = USART_Parity_Even;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode         = USART_Mode_Rx;    /* Only Rx pin is configured */
    USART_InitStruct.USART_Clock        = USART_Clock_Disable;
    USART_InitStruct.USART_CPOL         = USART_CPOL_Low;
    USART_InitStruct.USART_CPHA         = USART_CPHA_1Edge;
    USART_InitStruct.USART_LastBit      = USART_LastBit_Disable;

    /* Enable USART  */
    USART_Cmd(USART3, ENABLE);
    USART_Init(USART3, &USART_InitStruct);

    /* Enable IT on USART handler */
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART3, USART_IT_TC, DISABLE);
}


/*******************************************************************************
 * Function Name  : I2C1Init
 * Description    : Initializes the I2C 1 link.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void I2C1Init(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    /* Configure I2C_EE pins: SCL and SDA */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x38;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;

    /* I2C Peripheral Enable */
    I2C_Cmd(I2C1, ENABLE);
    /* Apply I2C configuration after enabling it */
    I2C_Init(I2C1, &I2C_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE); //Remap I2C1 to use PB8 and PB9
}


/*******************************************************************************
 * Function Name  : CanInit
 * Description    : Initializes the CAN controller module.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CanInit(void)
{
    CAN_InitTypeDef CAN_InitStruct;

    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN, DISABLE);
    GPIO_PinRemapConfig(GPIO_Remap2_CAN, DISABLE);

    /* Enable USART  */
    CAN_StructInit(&CAN_InitStruct);
//    CAN_Cmd(CAN, ENABLE);
    CAN_Init(&CAN_InitStruct);

    //Configure CAN
    CAN_StructInit(&CAN_InitStruct);

    /* CAN cell init */
    CAN_InitStruct.CAN_TTCM = DISABLE;
    CAN_InitStruct.CAN_ABOM = DISABLE;
    CAN_InitStruct.CAN_AWUM = DISABLE;
    CAN_InitStruct.CAN_NART = DISABLE;
    CAN_InitStruct.CAN_RFLM = DISABLE;
    CAN_InitStruct.CAN_TXFP = DISABLE;
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;

//  /* CAN Baudrate = 250kbps */
//  /* not working */
//  CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
//  CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
//  CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
//  CAN_InitStruct.CAN_Prescaler = 4;
//
//  /* CAN Baudrate = 500kbps */
    /* not working */
//  CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
//  CAN_InitStruct.CAN_BS1 = CAN_BS1_5tq;
//  CAN_InitStruct.CAN_BS2 = CAN_BS2_2tq;
//  CAN_InitStruct.CAN_Prescaler = 1;


#if (CAN_BAUDRATE == CAN_BAUDRATE_10KBPS)
    /* Not tested */
    //  /* CAN Baudrate = 10kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 400;
#elif CAN_BAUDRATE == CAN_BAUDRATE_20KBPS
    //  /* CAN Baudrate = 20kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 200;
#elif CAN_BAUDRATE == CAN_BAUDRATE_50KBPS
    //  /* CAN Baudrate = 50kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 80;
#elif CAN_BAUDRATE == CAN_BAUDRATE_100KBPS
    //  /* CAN Baudrate = 100kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 40;
#elif CAN_BAUDRATE == 125
    //  /* CAN Baudrate = 125kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 32;
#elif CAN_BAUDRATE == CAN_BAUDRATE_250KBPS
    //  /* CAN Baudrate = 250kbps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 16;
#elif CAN_BAUDRATE == CAN_BAUDRATE_500KBPS
    //  /* CAN Baudrate = 500kbps */
//  CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
//  CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
//  CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
//  CAN_InitStruct.CAN_Prescaler = 8;

    /* CAN Baudrate = 500kbps */
    /* or: system clock = 72MHz (PCLK1 = 36 MHz) */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_8tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStruct.CAN_Prescaler = 6;
#elif CAN_BAUDRATE == CAN_BAUDRATE_1MPBS
    /* CAN Baudrate = 1MBps */
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 4;
#endif

    CAN_Init(&CAN_InitStruct);

      /* CAN filter init */
//  #ifdef  __CAN1_USED__
      CAN_FilterInitStructure.CAN_FilterNumber = 0;
//  #else /*__CAN2_USED__*/
//    CAN_FilterInitStructure.CAN_FilterNumber = 14;
//  #endif  /* __CAN1_USED__ */
      CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
      CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
      CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0100 << 5;
      CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
      CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0700 << 5;
      CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
      CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
      CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
      CAN_FilterInit(&CAN_FilterInitStructure);

//  CAN_Init(&CAN_InitStruct);

    /* Enable IT on USART handler */
    CAN_ITConfig(CAN_IT_RQCP0, ENABLE);
    CAN_ITConfig(CAN_IT_FMP0, ENABLE);


    CAN_ITConfig(CAN_IT_RQCP1, ENABLE); /* Request completed mailbox 1 */
    CAN_ITConfig(CAN_IT_RQCP2, ENABLE); /* Request completed mailbox 2 */
    CAN_ITConfig(CAN_IT_TME, ENABLE);   /* Transmit mailbox empty */
    CAN_ITConfig(CAN_IT_FMP0, ENABLE);  /* FIFO 0 message pending */
    CAN_ITConfig(CAN_IT_FF0, ENABLE);   /* FIFO 0 full */
    CAN_ITConfig(CAN_IT_FOV0, ENABLE);  /* FIFO 0 overrun */
    CAN_ITConfig(CAN_IT_FMP1, ENABLE);  /* FIFO 1 message pending */
    CAN_ITConfig(CAN_IT_FF1, ENABLE);   /* FIFO 1 full */
    CAN_ITConfig(CAN_IT_FOV1, ENABLE);  /* FIFO 1 overrun */
}
//void CAN_Config(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure;
//
//  /* GPIO clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB1Periph_CAN);
////#ifdef  __CAN1_USED__
////  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN1, ENABLE);
////#else /*__CAN2_USED__*/
////  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN, ENABLE);
////#endif  /* __CAN1_USED__ */
//  /* Configure CAN pin: RX */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_RX;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
//
//  /* Configure CAN pin: TX */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_TX;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
//
// GPIO_PinRemapConfig(GPIO_Remapping_CAN , DISABLE);
//
//  /* CANx Periph clock enable */
//#ifdef  __CAN1_USED__
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//#else /*__CAN2_USED__*/
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
//#endif  /* __CAN1_USED__ */
//
//
//  /* CAN register init */
//  CAN_DeInit(CANx);
//  CAN_StructInit(&CAN_InitStructure);
//
//  /* CAN cell init */
//  CAN_InitStructure.CAN_TTCM = DISABLE;
//  CAN_InitStructure.CAN_ABOM = DISABLE;
//  CAN_InitStructure.CAN_AWUM = DISABLE;
//  CAN_InitStructure.CAN_NART = DISABLE;
//  CAN_InitStructure.CAN_RFLM = DISABLE;
//  CAN_InitStructure.CAN_TXFP = DISABLE;
//  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//
//  /* CAN Baudrate = 1MBps*/
//  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
//  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
//  CAN_InitStructure.CAN_Prescaler = 4;
//  CAN_Init(CAN, &CAN_InitStructure);
//
//  /* CAN filter init */
//#ifdef  __CAN1_USED__
//  CAN_FilterInitStructure.CAN_FilterNumber = 0;
//#else /*__CAN2_USED__*/
//  CAN_FilterInitStructure.CAN_FilterNumber = 14;
//#endif  /* __CAN1_USED__ */
//  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
//  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//  CAN_FilterInit(&CAN_FilterInitStructure);
//
//  /* Transmit */
//  CanTxMessage.StdId = 0x321;
//  CanTxMessage.ExtId = 0x01;
//  CanTxMessage.RTR = CAN_RTR_DATA;
//  CanTxMessage.IDE = CAN_ID_STD;
//  CanTxMessage.DLC = 1;
//}


/*******************************************************************************
 * Function Name  : ITInit
 * Description    : Initializes the interruptions.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void ITInit(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;

    /* USART1 */
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* USART2 */
    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* USART3 */
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* CAN */
    NVIC_InitStruct.NVIC_IRQChannel = CAN_RX1_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 200;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 200;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USB_HP_CAN_TX_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 200;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* TIMER4 */
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}


/*******************************************************************************
 * Function Name  : Teleinfo_LcdDisplay
 * Description    : Display Teleinformation values.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Teleinfo_LcdDisplay(void)
{
    /* Update LCD informations */
    LcdGotoXYFont(0,0);
    LcdStr(FONT_1X, (unsigned char *)"ADCO:");

    LcdGotoXYFont(0,1);
    LcdStr(FONT_1X, (unsigned char *)"PTEC:");

    LcdGotoXYFont(6,1);
    LcdStr(FONT_1X, (unsigned char *) &(TIC_info.PTEC[0]) );

    LcdGotoXYFont(0,2);
    LcdStr(FONT_1X, (unsigned char *)"HCHC:");

    LcdGotoXYFont(5,2);
    LcdStr(FONT_1X, (unsigned char *) &(TIC_info.HCHC[0]) );

    LcdGotoXYFont(0,3);
    LcdStr(FONT_1X, (unsigned char *)"HCHP:");

    LcdGotoXYFont(5,3);
    LcdStr(FONT_1X, (unsigned char *) &(TIC_info.HCHP[0]) );

    LcdGotoXYFont(0,4);
    LcdStr(FONT_1X, (unsigned char *)"IINST:");

    LcdGotoXYFont(7,4);
    LcdStr(FONT_1X, (unsigned char *) &(TIC_info.IINST[0]) );

    LcdUpdate();
}


/*******************************************************************************
 * Function Name  : PWMInit
 * Description    : Initializes the PWM.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void PWMInit(void)
{
    TIM_TimeBaseInitTypeDef timer;
    TIM_OCInitTypeDef timerPWM1, timerPWM2, timerPWM3;

    /* Enable peripheral clock for TIMER 3 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Initialize TIMER 3 */
    TIM_TimeBaseStructInit(&timer);
    timer.TIM_Prescaler = 720;
    timer.TIM_Period = PERIOD;
    timer.TIM_ClockDivision = 0;
    timer.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &timer);

    /* Configure TIM3 - Ch1 */
    TIM_OCStructInit(&timerPWM1);
    timerPWM1.TIM_OCMode = TIM_OCMode_PWM1;
    timerPWM1.TIM_Channel = TIM_Channel_1;
    timerPWM1.TIM_Pulse = 1000; //0;
    timerPWM1.TIM_OCPolarity = TIM_OCPolarity_High;

    /* Configure TIM3 - Ch2 */
    TIM_OCStructInit(&timerPWM2);
    timerPWM2.TIM_OCMode = TIM_OCMode_PWM1;
    timerPWM2.TIM_Channel = TIM_Channel_2;
    timerPWM2.TIM_Pulse = 1000;
    timerPWM2.TIM_OCPolarity = TIM_OCPolarity_High;

    /* Configure TIM3 - Ch3 */
    TIM_OCStructInit(&timerPWM3);
    timerPWM3.TIM_OCMode = TIM_OCMode_PWM1;
    timerPWM3.TIM_Channel = TIM_Channel_3;
    timerPWM3.TIM_Pulse = 1000;
    timerPWM3.TIM_OCPolarity = TIM_OCPolarity_High;

    /* Init timer */
    TIM_OCInit(TIM3, &timerPWM1);
    TIM_OCInit(TIM3, &timerPWM2);
    TIM_OCInit(TIM3, &timerPWM3);

    /* Reinitialize timer values */
    TIM3->CCR1 = 0; //Pulse Red
    TIM3->CCR2 = 0; //Pulse Green
    TIM3->CCR3 = 0; //Pulse Blue

    /* Enable TIM3 */
    TIM_Cmd(TIM3, ENABLE);
}


/*******************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void RCC_Configuration(void)
{
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS) {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* Flash 2 wait state */
        FLASH_SetLatency(FLASH_Latency_2);

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 9 = 72 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        /* Enable PLL */
        RCC_PLLCmd(ENABLE);

        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {
        }

        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x08) {
        }
    }
}


/*******************************************************************************
 * Function Name  : NVIC_Configuration
 * Description    : Configures Vector Table base location.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void NVIC_Configuration(void) 
{
#ifdef  VECT_TAB_RAM  
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}

/*******************************************************************************
 * Function Name  : Delay
 * Description    : Inserts a delay time.
 * Input          : nCount: specifies the delay time length.
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Delay(vu32 nCount) 
{
    for (; nCount != 0; nCount--)
        ;
}

#ifdef  DEBUG
/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void assert_failed(u8* file, u32 line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif



/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
