#ifndef TELEINFO_H
#define TELEINFO_H
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

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	unsigned char ADCO[12+1];
	unsigned char OPTARIF[4+1];
	unsigned char ISOUSC[2+1];
	//Option Base:
//	unsigned char BASE[9+1];
	//Option Heures Creuses:
	unsigned char HCHC[9+1];
	unsigned char HCHP[9+1];
	//Option EJP:
//	unsigned char EJPHN[9+1];
//	unsigned char EJPHPM[9+1];
	//Option Tempo:
//	unsigned char BBRHCJB[9+1];
//	unsigned char BBRHPJB[9+1];
//	unsigned char BBRHCJW[9+1];
//	unsigned char BBRHPJW[9+1];
//	unsigned char BBRHCJR[9+1];
//	unsigned char BBRHPJR[9+1];
//	unsigned char PEJP[2+1];
	unsigned char PTEC[4+1];
//	unsigned char DEMAIN[4+1];
	unsigned char IINST[3+1];
	unsigned char ADPS[3+1];
	unsigned char IMAX[3+1];
	unsigned char PAPP[4+1];
	unsigned char HHPHC[1+1];
	unsigned char MOTDETAT[6+1];
} T_TIC_INFO;

/* Private define ------------------------------------------------------------*/
#define ASCII_STX	0x2  //Start of Text
#define ASCII_ETX 	0x3  //End of Text
#define ASCII_LF	0xa  //Start of label
#define ASCII_CR	0xd  //End of label
#define ASCII_SP	0x20 //Space

enum
{
	INVALID,
	ADCO,
	OPTARIF,
	ISOUSC,
	//Option base:
//	BASE,
	//Option Heures Creuses:
	HCHC,
	HCHP,
	//Option Ejp:
//	EJPHN,
//	EJPHPM,
	//Option Tempo:
//	BBRHCJB,
//	BBRHPJB,
//	BBRHCJW,
//	BBRHPJW,
//	BBRHCJR,
//	BBRHPJR,
//	PEJP,
	PTEC,
//	DEMAIN,
	IINST,
//	ADPS,
	IMAX,
	PAPP,
	HHPHC,
	MOTDETAT
} TIC_LABEL_TYPE;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern T_TIC_INFO TIC_info;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
 * Function Name  : 
 * Description    : 
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void teleinfo_Init(void);
int teleinfo_rawData_receive(u8 rawData);
void Teleinfo_Mgt();
unsigned char TIC_check_frame(unsigned char str[30], unsigned char *labelCode, unsigned long int *valueCode);
unsigned long int Ascii2Int(unsigned char *str, unsigned char len);
unsigned char TIC_FillInInfo(unsigned char labelCode, unsigned int val);
unsigned char TIC_getLabelCode(unsigned char str[5]);
unsigned char TIC_CRC(unsigned char *str);
void Teleinfo_USART_Init(USART_TypeDef* USARTx);


#endif /* TELEINFO_H */

