/********************************************************************************
 * File Name          : teleinfo.c
 * Date               : 10/08/2007
 * Description        : Main program body
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"
#include "Fifo.h"
#include "teleinfo.h"

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
	unsigned char str[30];
}TIC_label_str;

typedef struct
{
    // FIFO struct for TIC messages
    unsigned char **buff;		// raw data buffer
    unsigned char size;  		// FIFO length
    unsigned char WriteIdx; 	// Next position to write an element
    unsigned char ReadIdx;  	// Next Element to read
    unsigned char NumElem;  	// Total of elements currently in the FIFO
    unsigned char NumMaxElem;  	// maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_TIC_FIFO;


T_TIC_FIFO TIC_Fifo;
#define TIC_FIFO_LENGTH     55
unsigned char TIC_FIFO_Buff[TIC_FIFO_LENGTH][30];



/* Private define ------------------------------------------------------------*/
#define MODE1 1
#define MODE2 2
#define TIC_CRC_MODE MODE1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 rawDataTab[170];
u16 cptRawData=0;
u8 cptTIC_label=0;

T_TIC_INFO TIC_info;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


void teleinfo_Init(void)
{
	// Initialize Fifo
	TIC_Fifo.buff 		= &TIC_FIFO_Buff[0][0];
	TIC_Fifo.size 		= TIC_FIFO_LENGTH;
	TIC_Fifo.WriteIdx 	= 0;
	TIC_Fifo.ReadIdx 	= 0;
	TIC_Fifo.NumElem 	= 0;
	TIC_Fifo.NumMaxElem = 0;
	TIC_Fifo.overrun    = 0;
}


/*******************************************************************************
 * Function Name  : teleinfo_rawData_receive
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int teleinfo_rawData_receive(u8 rawData)
{

	if( rawData == ASCII_LF ) //LF Start of label
	{
		// store
		cptTIC_label=0;
		TIC_FIFO_Buff[TIC_Fifo.WriteIdx][cptTIC_label++] = rawData;
	}
	else if( rawData == ASCII_CR ) //CR End of label
	{
		//store and increment fifo
		TIC_FIFO_Buff[TIC_Fifo.WriteIdx][cptTIC_label] = rawData;

		TIC_Fifo.NumElem++;
		if(TIC_Fifo.NumElem > TIC_Fifo.NumMaxElem ) // For debug purpose
		{
			TIC_Fifo.NumMaxElem = TIC_Fifo.NumElem;
		}

		TIC_Fifo.WriteIdx++;
		if(TIC_Fifo.WriteIdx>=55)
		{
			TIC_Fifo.WriteIdx=0;
		}
	}
	else if( rawData == ASCII_STX ) //STX Start of Transmission
	{
		// do nothing
	}
	else if( rawData == ASCII_ETX ) //ETX End of Transmission - !!! if last caracter was not a CR, label transmission is not complete (telereport access on-going)
	{
		// do nothing
	}
	else
	{
		//store car
		TIC_FIFO_Buff[TIC_Fifo.WriteIdx][cptTIC_label++] = rawData;
	}


//	TIC_Fifo


	//temporary added for debug:
	if( (rawData == ASCII_ETX) /*&& (TIC_Fifo.WriteIdx > 30)*/ )
	{
		Teleinfo_Mgt();
	}
	
	return 0;
}

void Teleinfo_Mgt()
{
	unsigned char car, cpt=0, labelLen=0, valueLen=0;
	unsigned char label, value;
	unsigned char WriteIdx = TIC_Fifo.WriteIdx;
	unsigned char *ReadIdx = &(TIC_Fifo.ReadIdx);

	while(*ReadIdx != WriteIdx)
	{
		//check string validity and split values
		if( TIC_check_frame(TIC_FIFO_Buff[*ReadIdx], &label, &value ) )
		{
			//Frame is valid, update info
//			if( label != INVALID )
//			{
//				TIC_FillInInfo(label, value);
//			}
		}
		else
		{
			//ignore frame
		}


		// Manage Fifo
		if(TIC_Fifo.NumElem>0)
		{
			TIC_Fifo.NumElem--;
		}

		//		(*ReadIdx)++;
		//		if( *(ReadIdx) >= (TIC_Fifo.size) );
		//		{
		//			(*ReadIdx) = 0;
		//		}

		TIC_Fifo.ReadIdx++;
		if(TIC_Fifo.ReadIdx>=55)
		{
			TIC_Fifo.ReadIdx=0;
		}

	}


}

unsigned char TIC_check_frame(unsigned char str[30], unsigned char *labelCode, unsigned long int *valueCode)
{
	unsigned char strLen=0, i;
	unsigned char labelStr[10], valueStr[12], CRC;
	unsigned char labelLen=0, valueLen=0;

	unsigned char IsValid=FALSE;


	//Read each line received
	if( str[strLen++] == ASCII_LF ) //Check line begins with LF
	{
		//Get label
		do
		{
			labelStr[labelLen++] = str[strLen++];
		}
		while(str[strLen] != ASCII_SP); //space

		//ignore space
		strLen++;

		//Get value
		do
		{
			valueStr[valueLen++] = str[strLen++];
		}
		while(str[strLen] != ASCII_SP); //space

		//ignore space
		strLen++;

		//Get CRC
		do
		{
			//1 car long followed by CR
			CRC = str[strLen++];
		}
		while(str[strLen] != ASCII_CR); //CR

		//all informations are get, now compute CRC
		if( TIC_CRC(str) == CRC)
		{
			//Valid CRC
			IsValid = TRUE;

//			*labelCode = TIC_getLabelCode(labelStr);
//			*valueCode = Ascii2Int(valueStr, valueLen);

			switch (labelStr[0])
			{
				case 'A': //ADCO
//					labelCode = ADCO;
					for(i=0; i<valueLen; i++)
						TIC_info.ADCO[i]=valueStr[i];
					TIC_info.ADCO[i]='\0';
				break;

				case 'I':
					if(labelStr[1] == 'I')
					{
//						labelCode = IINST;
						for(i=0; i<valueLen; i++)
							TIC_info.IINST[i]=valueStr[i];
						TIC_info.IINST[i]='\0';
					}
					else if(labelStr[1] == 'M')
					{
//						labelCode = IMAX;
						for(i=0; i<valueLen; i++)
							TIC_info.IMAX[i]=valueStr[i];
						TIC_info.IMAX[i]='\0';
					}
					else if(labelStr[1] == 'S')
					{
//						labelCode = ISOUSC;
						for(i=0; i<valueLen; i++)
							TIC_info.ISOUSC[i]=valueStr[i];
						TIC_info.ISOUSC[i]='\0';
					}
					else
					{
//						labelCode = INVALID;
					}
				break;

				case 'O':
//					labelCode = OPTARIF;
					for(i=0; i<valueLen; i++)
						TIC_info.OPTARIF[i]=valueStr[i];
					TIC_info.OPTARIF[i]='\0';
				break;

				case 'H':
					if(labelStr[3] == 'C')
					{
//						labelCode = HCHC;
						for(i=0; i<valueLen; i++)
							TIC_info.HCHC[i]=valueStr[i];
						TIC_info.HCHC[i]='\0';
					}
					else if(labelStr[3] == 'P')
					{
//						labelCode = HCHP;
						for(i=0; i<valueLen; i++)
								TIC_info.HCHP[i]=valueStr[i];
						TIC_info.HCHP[i]='\0';
					}
					else if(labelStr[3] == 'H')
					{
//						labelCode = HHPHC;
						for(i=0; i<valueLen; i++)
							TIC_info.HHPHC[i]=valueStr[i];
						TIC_info.HHPHC[i]='\0';
					}
					else
					{
//						labelCode = INVALID;
					}
					break;

				case 'P':
					if(labelStr[1] == 'T')
					{
//						labelCode = PTEC;
						for(i=0; i<valueLen; i++)
							TIC_info.PTEC[i]=valueStr[i];
						TIC_info.PTEC[i]='\0';
					}
					else if(labelStr[1] == 'A')
					{
//						labelCode = PAPP;
						for(i=0; i<valueLen; i++)
							TIC_info.PAPP[i]=valueStr[i];
						TIC_info.PAPP[i]='\0';
					}
					break;

				case 'M':
//					labelCode = MOTDETAT;
					for(i=0; i<valueLen; i++)
						TIC_info.MOTDETAT[i]=valueStr[i];
					TIC_info.MOTDETAT[i]='\0';
					break;

				default:
//					labelCode = INVALID;
					break;

			}

		}

	}

	return IsValid;
}

unsigned long int Ascii2Int(unsigned char *str, unsigned char len)
{
	unsigned char i;
	unsigned int tmp=0;

	for(i=0; i<len; i++)
	{
		tmp = tmp*10;
		tmp += ( str[i] - 48 );
	}

	return tmp;
}

unsigned char TIC_FillInInfo(unsigned char labelCode, unsigned int val)
{
//	switch (labelCode)
//	{
//	case ADCO:
//		TIC_info.ADCO = val;
//		break;
//	case OPTARIF:
//		TIC_info.OPTARIF = val;
//		break;
//	case ISOUSC:
//		TIC_info.ISOUSC = val;
//		break;
//	case HCHC:
//		TIC_info.HCHC = val;
//		break;
//	case HCHP:
//		TIC_info.HCHP = val;
//		break;
//	case PTEC:
//		TIC_info.PTEC = val;
//		break;
//	case IINST:
//		TIC_info.IINST = val;
//		break;
//	case IMAX:
//		TIC_info.IMAX = val;
//		break;
//	case PAPP:
//		TIC_info.PAPP = val;
//		break;
//	case HHPHC:
//		TIC_info.HHPHC = val;
//		break;
//	case MOTDETAT:
//		TIC_info.MOTDETAT = val;
//		break;
//	}

}

unsigned char TIC_getLabelCode(unsigned char str[5])
{
	unsigned char labelCode;

	switch (str[0])
	{
		case 'A': //ADCO
			labelCode = ADCO;
		break;

		case 'I':
			if(str[1] == 'I')
				labelCode = IINST;
			else if(str[1] == 'M')
				labelCode = IMAX;
			else if(str[1] == 'S')
				labelCode = ISOUSC;
			else
				labelCode = INVALID;
		break;

		case 'O':
			labelCode = OPTARIF;
		break;

		case 'H':
			if(str[3] == 'C')
				labelCode = HCHC;
			else if(str[3] == 'P')
				labelCode = HCHP;
			else if(str[3] == 'H')
				labelCode = HHPHC;
			else
				labelCode = INVALID;
			break;

		case 'P':
			if(str[1] == 'T')
				labelCode = PTEC;
			else if(str[1] == 'A')
				labelCode = PAPP;
			break;

		case 'M':
			labelCode = MOTDETAT;
			break;

		default:
			labelCode = INVALID;
			break;
	}

	return labelCode;
}

unsigned char TIC_CRC(unsigned char *str)
{
	/* CRC is computed from the input string by summing up each byte of the string.
	 * Depending on the mode, the following characters are taken into account:
	 * in mode 1: LABEL + SP + DATA
	 * in mode 2: LABEL + SP + DATA + SP
	 */
	unsigned char tmp=0, i, sp=0;

	// Compute CRC from string (only LowByte is kept)
	for(i=0; i<30; i++)
	{
		if(str[i] == ASCII_LF) //Beginning of the string
		{
			tmp=0;
		}
		else if( (str[i] == ASCII_SP) && (sp==0)) //End of label
		{
			tmp += str[i];
			sp++;
		}
		else if(str[i] == ASCII_SP) //End of value
		{
#if TIC_CRC_MODE == MODE2
			// In mode 2, add compute CRC with CR
			tmp += str[i];
#endif
			break;
		}
		else if( (str[i] == ASCII_CR) || (str[i] == ASCII_ETX) ) //End if string
		{
			//Error case: End of string reached.
			break;
		}
		else
		{
			tmp += str[i];
		}
	}

	// Mask with 0x3F
	tmp &= 0x3F;

	//Add 0x20 to display ASCII character
	tmp += 0x20;

	return tmp;
}

/*******************************************************************************
 * Function Name  : Teleinfo_USART_Init
 * Description    : Initialize USART link to be used with EDF smart meters
 * Input          : USART module to initialize
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Teleinfo_USART_Init(USART_TypeDef* USARTx)
{
	USART_InitTypeDef USART_InitStruct;

	/* Enable USART  */
	USART_InitStruct.USART_BaudRate 	= 0x04B0; /* 1200 Baud */
	USART_InitStruct.USART_WordLength 	= USART_WordLength_8b;
	USART_InitStruct.USART_StopBits 	= USART_StopBits_1;
	USART_InitStruct.USART_Parity 		= USART_Parity_Even;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode			= USART_Mode_Rx; 	/* Only Rx pin is enabled */
	USART_InitStruct.USART_Clock 		= USART_Clock_Disable;
	USART_InitStruct.USART_CPOL 		= USART_CPOL_Low;
	USART_InitStruct.USART_CPHA 		= USART_CPHA_1Edge;
	USART_InitStruct.USART_LastBit 		= USART_LastBit_Disable;

	USART_Cmd(USARTx, ENABLE);
	USART_Init(USARTx, &USART_InitStruct);

	/* Enable IT on USART handler */
	USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
	USART_ITConfig(USARTx, USART_IT_TC, DISABLE);
}




