/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: hp
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include "util/delay.h"
#include "UART_int.h"
#include "Timer_int.h"

//main slave -> Project1
void main(void)
{
	u16 x=0;
	//pins

	//SS
	DIO_SetPinDirection(PORTB,PIN_4,Input);
	//MOSI
	DIO_SetPinDirection(PORTB,PIN_5,Input);
	//MISO
	DIO_SetPinDirection(PORTB,PIN_6,Output);
	//SCK
	DIO_SetPinDirection(PORTB,PIN_7,Input);

	SPI_SlaveInit();

	//DC Motor
	DIO_SetPinDirection(PORTC,PIN_0,Output);
	DIO_SetPinValue(PORTC,PIN_0,LOW);

	while(1)
	{
		x=SPI_Tranceive(70);
		if(x >= 26)
		{
			DIO_SetPinValue(PORTC,PIN_0,HIGH);
		}
		else
		{
			DIO_SetPinValue(PORTC,PIN_0,LOW);
		}
	}
}
