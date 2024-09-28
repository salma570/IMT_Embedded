/*
 * UART_int.h
 *
 *  Created on: Sep 3, 2024
 *      Author: hp
 */

#ifndef UART_INT_H_
#define UART_INT_H_

void UART_init(void);
void UART_transmit(u8 Copy_u8Data);
u8 UART_receive(void);

#endif /* UART_INT_H_ */
