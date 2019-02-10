/*
 * serial.c
 *
 *  Created on: Feb 9, 2019
 *      Author:
 */

#include "stm32f10x_can.h"
#include "serial.h"
#include "Fifo_Cfg.h"

typedef struct
{
	unsigned char buff[20];		// pointer to raw data
	unsigned char length;		// Effective length of the string
	unsigned char pos;			// Current position/character in the string
} T_FIFO_TEXT_ELEM;

typedef struct
{
    // FIFO struct for TIC messages
	T_FIFO_TEXT_ELEM strBuff[10];       // raw data buffer
    unsigned char size;         // FIFO length
    unsigned char WriteIdx;     // Next position to write an element
    unsigned char ReadIdx;      // Next Element to read
    unsigned char NumElem;      // Total of elements currently in the FIFO
    unsigned char NumMaxElem;   // maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_SERIAL_FIFO;


/* T_SERIAL_FIFO TIC_Fifo;
#define TIC_FIFO_SIZE	    10
#define TIC_FIFO_LENGTH     20
T_FIFO_TEXT_ELEM SERIAL_FIFO_Buff[TIC_FIFO_SIZE]; */

T_SERIAL_FIFO serialFifo;

unsigned char serialStrBuff[50];
unsigned char serialStrBuff_Len = 0;
unsigned char serialStrBuff_Pos = 0;

void serial_SendMessage(unsigned char *strPtr, unsigned char size)
{
	unsigned char i;

	for(i=0; i<size; i++)
	{
		FIFO_add( &SERIAL_TX_FIFO, strPtr[i] );
	}

	// Send the first character
	serial_SendChar();
}


void serial_SendChar(void)
{
	unsigned char data;
	if( FIFO_read( &SERIAL_TX_FIFO, &data) )
	{
		USART_SendData(USART2, data);
	}
}

typedef enum
{
    SERIALMENU_IDLE,
    SERIALMENU_WAITCMD,
	SERIALMENU_ACTION,
}T_SerialMenuStep;

typedef enum
{
	SERIALMENU_INVALID,
    SERIALMENU_0showHelp,
    SERIALMENU_1showOut,
	SERIALMENU_2SetOut,
}T_SerialMenuAction;


T_SerialMenuStep serialMenuStep;
T_SerialMenuAction serialMenu_Action=SERIALMENU_INVALID;
void serialMenu(void)
{
	switch (serialMenuStep )
	{
		case SERIALMENU_IDLE:
			serial_SendMessage("\n\nAction:\n", 10);
			serial_SendMessage("0-show help\n", 12);
			serial_SendMessage("1-show outputs\n", 15);
			serial_SendMessage("2-set outputs\n", 14);
			serialMenuStep = SERIALMENU_WAITCMD;
			break;

		case SERIALMENU_WAITCMD:
			break;

		case SERIALMENU_ACTION:
			serial_SendMessage("cmd:\n", 5);
			if(serialMenu_Action==SERIALMENU_0showHelp)
			{
				serialMenuStep = SERIALMENU_IDLE;
			}
			break;

		default:
			serialMenuStep = SERIALMENU_IDLE;
	}
}
