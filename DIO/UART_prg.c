/*
 * UART_prg.c
 *
 *  Created on: Sep 3, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "UART_prv.h"
#include "UART_int.h"

void UART_init(void)
{

	UCSRC_Register=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	CLR_BIT(UCSRB_Register,UCSZ2);

	//Enable Receive & Transmit
	SET_BIT(UCSRB_Register,RXEN);
	SET_BIT(UCSRB_Register,TXEN);

	//9600 BaudRate
	UBRRL_Register=51;
}

void UART_transmit(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA_Register,UDRE)==0);
	UDR_Register=Copy_u8Data;
}

u8 UART_receive(void)
{
	while(GET_BIT(UCSRA_Register,RXC)==0);
	return UDR_Register;
}
