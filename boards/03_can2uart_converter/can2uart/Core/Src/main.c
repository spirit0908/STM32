/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay (int a)
{
  volatile int i,j;
  for (i=0 ; i < a ; i++)
  {
     j++;
  }
  return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
	    Task_Manager_IT();
	}
}

uint8_t UART1_rxBuffer[40] = {0};
uint8_t UART1_pos=0;

unsigned char canMailBox;
unsigned char * pTxMailbox=&canMailBox;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	unsigned char echo = 1;
	unsigned char CanDlc=0;
	unsigned int CanId;
	unsigned char CanData[8];


    CAN_TxHeaderTypeDef canHeader;


	if(huart->Instance == USART1)
	{

        if( (UART1_rxBuffer[UART1_pos] == '\n') || (UART1_rxBuffer[UART1_pos] == '\r') || (UART1_pos >= 40) )
        {
    	    HAL_UART_Transmit(&huart1, (uint8_t*)"received: ", 10, 100);
            HAL_UART_Transmit(&huart1, UART1_rxBuffer, UART1_pos, 100);
    	    HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 100);

            //Uart2can_RxIndication(UART1_rxBuffer);
    	    if( Uart2can_Extract(UART1_rxBuffer, &CanId, &CanDlc, CanData) == 0)
    	    {
    	    	canHeader.StdId = CanId;
    	    	canHeader.DLC = CanDlc;
    	        HAL_CAN_AddTxMessage(&hcan, &canHeader, CanData, pTxMailbox);
    	    }
    	    UART1_pos = 0;
        }
        else if( UART1_rxBuffer[UART1_pos] == '\177' )
		{
        	if(UART1_pos > 0)
              UART1_pos--;
		}
        else
        {
        	UART1_pos++;
        }

        if( echo == 1 )
        {
            HAL_UART_Transmit(&huart1, UART1_rxBuffer[UART1_pos], 1, 100);
        }

        canHeader.StdId = 0x100;
        canHeader.ExtId = 0;
        canHeader.IDE = CAN_ID_STD;
        canHeader.RTR = CAN_RTR_DATA;
        canHeader.DLC=8;
        canHeader.TransmitGlobalTime = DISABLE;

        /* Reenable uart1 interrupt */
        HAL_UART_Receive_IT(&huart1, &UART1_rxBuffer[UART1_pos], 1);
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef CanHeader;
  uint8_t CanRxData[8];

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef CanHeader;
  uint8_t CanRxData[8];

  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanHeader, CanRxData);

  HAL_UART_Transmit(&huart1, (uint8_t*)"received can message: ", 22, 100);
  HAL_UART_Transmit(&huart1, ((CanHeader.StdId>>8)&0xFF+'0'), 1, 100);
  HAL_UART_Transmit(&huart1, (CanHeader.StdId&0xFF+'0'), 3, 100);
  HAL_UART_Transmit(&huart1, CanHeader.DLC,   1, 100);
  HAL_UART_Transmit(&huart1, CanRxData[0], 2, 100);

  HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 100);


  if (CanHeader.IDE == CAN_ID_STD )
  {
      // Traitement des donnéess


  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  unsigned char str_buff[15] ={0};


  CAN_TxHeaderTypeDef canHeader;
  unsigned char canBuff[8]={1, 2, 3, 4, 5, 6, 7, 8};
  unsigned char canMailBox;
  unsigned char * pTxMailbox=&canMailBox;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  /* Configure the CAN Filter */
  {
    CAN_FilterTypeDef  sFilterConfig;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
      /* Filter configuration Error */
      Error_Handler();
    }

    /* Start the CAN peripheral */
  //  if (HAL_CAN_Start(&hcan) != HAL_OK)
  //  {
  //    /* Start Error */
  //    Error_Handler();
  //  }

    /* Activate CAN RX notification */
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }

    /* Configure Transmission process */
    canHeader.StdId = 0x321;
    canHeader.ExtId = 0x01;
    canHeader.RTR = CAN_RTR_DATA;
    canHeader.IDE = CAN_ID_STD;
    canHeader.DLC = 2;
    canHeader.TransmitGlobalTime = DISABLE;

  }
  HAL_TIM_Base_Start_IT(&htim4);


//  HAL_CAN_Start(&hcan); //start CAN
//  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts

  hcan.Instance->MCR = 0x60; //IMPORTANT FOR DEBUG!!!!!!!
  TaskManager_Init();

  HAL_UART_Receive_IT (&huart1, UART1_rxBuffer, 1);
  HAL_UART_Transmit(&huart1, (uint8_t *)"welcome\r\n", 9, 100);

  //HAL_CAN_WakeUp(&hcan);

  canHeader.StdId = 0x012;
  canHeader.ExtId = 0x21;
  canHeader.IDE = CAN_ID_STD;
  canHeader.RTR = 0;
  canHeader.DLC=1;
  canHeader.TransmitGlobalTime = DISABLE;

  HAL_CAN_AddTxMessage(&hcan, &canHeader, canBuff, pTxMailbox);



//  CDC_Transmit_FS((uint8_t*)"USB serial initialized\n", 23);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    TaskManager();


    {
        uint32_t TxMailbox;
        uint8_t TxData[8];
        CAN_TxHeaderTypeDef TxMessage;


        TxData[0] = 0xAB;
        TxData[1] = 0xCD;

        TxMessage.DLC = 2;
		TxMessage.IDE = CAN_ID_STD;
		TxMessage.RTR = 0;
		TxMessage.StdId = 0x234;
		TxMessage.TransmitGlobalTime = DISABLE;

     //   HAL_CAN_AddTxMessage(&hcan, &TxMessage, TxData, &TxMailbox);
    }
    //HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USB_LP_CAN1_RX0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* CAN1_RX1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 6;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7200;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 50;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
