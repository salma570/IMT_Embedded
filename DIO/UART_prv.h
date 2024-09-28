/*
 * UART_prv.h
 *
 *  Created on: Sep 3, 2024
 *      Author: hp
 */

#ifndef UART_PRV_H_
#define UART_PRV_H_

#define UDR_Register     *((volatile u8*)(0x2C))
#define UCSRA_Register   *((volatile u8*)(0x2B))
#define UCSRB_Register   *((volatile u8*)(0x2A))
#define UCSRC_Register   *((volatile u8*)(0x40))
#define UBRRL_Register   *((volatile u8*)(0x29))

#define RXEN  	4
#define TXEN  	3

#define URSEL 	7
#define UCSZ0 	1
#define UCSZ1 	2
#define UCSZ2 	2

#define UDRE 	5
#define RXC 	7

#endif /* UART_PRV_H_ */
