/*
 * serial.h
 *
 *  Created on: Feb 9, 2019
 *      Author: spirit
 */

#ifndef SERIAL_H_
#define SERIAL_H_

void serial_SendMessage(unsigned char *strPtr, unsigned char size);
void serial_SendChar(void);
void serialMenu(void);

#endif /* SERIAL_H_ */
