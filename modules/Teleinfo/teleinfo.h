/********************************************************************************
 * File Name          : teleinfo.c
 * Date               : 10/08/2007
 * Description        : Main program body
 *******************************************************************************/
#ifndef TELEINFO_H
#define TELEINFO_H

/************************************************************************
* INCLUDES *
************************************************************************/
#include "stm32f10x_lib.h"

#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"

/************************************************************************
* DEFINES *
************************************************************************/
#define ASCII_STX   0x2  //Start of Text
#define ASCII_ETX   0x3  //End of Text
#define ASCII_LF    0xa  //Start of label
#define ASCII_CR    0xd  //End of label
#define ASCII_SP    0x20 //Space

/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct
{
    unsigned char ADCO[12+1];
    unsigned char OPTARIF[4+1];
    unsigned char ISOUSC[2+1];
    //Option Base:
//  unsigned char BASE[9+1];
    //Option Heures Creuses:
    unsigned char HCHC[9+1];
    unsigned char HCHP[9+1];
    //Option EJP:
//  unsigned char EJPHN[9+1];
//  unsigned char EJPHPM[9+1];
    //Option Tempo:
//  unsigned char BBRHCJB[9+1];
//  unsigned char BBRHPJB[9+1];
//  unsigned char BBRHCJW[9+1];
//  unsigned char BBRHPJW[9+1];
//  unsigned char BBRHCJR[9+1];
//  unsigned char BBRHPJR[9+1];
//  unsigned char PEJP[2+1];
    unsigned char PTEC[4+1];
//  unsigned char DEMAIN[4+1];
    unsigned char IINST[3+1];
    unsigned char ADPS[3+1];
    unsigned char IMAX[3+1];
    unsigned char PAPP[4+1];
    unsigned char HHPHC[1+1];
    unsigned char MOTDETAT[6+1];
} T_TIC_INFO;


/* typedef struct
{
    unsigned char str[30];
}TIC_label_str; */


typedef struct
{
    // FIFO struct for TIC messages
    unsigned char **buff;       // raw data buffer
    unsigned char size;         // FIFO length
    unsigned char WriteIdx;     // Next position to write an element
    unsigned char ReadIdx;      // Next Element to read
    unsigned char NumElem;      // Total of elements currently in the FIFO
    unsigned char NumMaxElem;   // maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_TIC_FIFO;


enum
{
    INVALID,
    ADCO,
    OPTARIF,
    ISOUSC,
    //Option base:
//  BASE,
    //Option Heures Creuses:
    HCHC,
    HCHP,
    //Option Ejp:
//  EJPHN,
//  EJPHPM,
    //Option Tempo:
//  BBRHCJB,
//  BBRHPJB,
//  BBRHCJW,
//  BBRHPJW,
//  BBRHCJR,
//  BBRHPJR,
//  PEJP,
    PTEC,
//  DEMAIN,
    IINST,
//  ADPS,
    IMAX,
    PAPP,
    HHPHC,
    MOTDETAT
} TIC_LABEL_TYPE;


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern T_TIC_INFO TIC_info;


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void teleinfo_Init(void);
int teleinfo_rawByte_receive(u8 rawByte);
void Teleinfo_Mgt(void);
unsigned char TIC_check_frame(unsigned char str[30], unsigned char *labelCode, unsigned long int *valueCode);
unsigned long int Ascii2Int(unsigned char *str, unsigned char len);
unsigned char TIC_FillInInfo(unsigned char labelCode, unsigned int val);
unsigned char TIC_getLabelCode(unsigned char str[5]);
unsigned char TIC_CRC(unsigned char *str);
void Teleinfo_USART_Init(USART_TypeDef* USARTx);


#endif /* TELEINFO_H */
